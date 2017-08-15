<?php

/**
 * @file
 * Field handlers to render actions for queue items and sets.
 */

abstract class IslandoraQaViewsFieldHandlerActions extends views_handler_field {
  /**
   * Get default options.
   *
   * @see views_handler_field::option_definition()
   */
  protected function optionDefinition() {
    return parent::option_definition();
  }

  /**
   * Get form to customize options.
   *
   * @see views_handler_field::options_form()
   */
  protected function optionsForm(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['action_base_path'] = array(
      '#type' => 'textfield',
      '#title' => t('Base action path'),
      '#description' => t('The path under which most actions are called.'),
      '#default_value' => $this->actionBasePath(),
      '#weight' => 0,
    );
  }

  /**
   * Accessor for action_base_path.
   */
  protected function actionBasePath() {
    return isset($this->options['action_base_path']) ?
      $this->options['action_base_path'] :
      'no/path/set';
  }

  /**
   * Actually render the value for this item.
   *
   * @param object $values
   *   All values available in the given row.
   *
   * @return string
   *   Rendered markup.
   */
  protected function renderValues($values) {
    $views_module_path = drupal_get_path('module', 'views');

    $value = array(
      '#attached' => array(
        'css' => array(
          "$views_module_path/css/views-admin.ctools.css",
          "$views_module_path/css/views-admin.seven.css",
        ),
      ),
      '#prefix' => '<span class="ctools-dropbutton-wrapper">',
      '#suffix' => '</span>',
      '#theme' => 'links__ctools_dropbutton',
      '#links' => $this->getLinks($values),
    );
    return drupal_render($value);
  }

  /**
   * Get links to render as actions.
   *
   * @param object $values
   *   The other values available in the given row.
   *
   * @return array
   *   An array of links, as accepted in the 'links' parameter of
   *   theme_links(). Each should contain at least:
   *   - title: The link title.
   *   - href: The URL to which to link.
   */
  abstract protected function getLinks($values);

  // @codingStandardsIgnoreStart
  // XXX: views uses underscores in its function names... Let's map 'em, so the
  // code doing the lifting can actually be run through coder.
  function option_definition() {
    return $this->optionDefinition();
  }

  function options_form(&$form, &$form_state) {
    $this->optionsForm($form, $form_state);
  }

  function allow_advanced_render() {
    return FALSE;
  }

  function is_value_empty($value, $empty_zero, $no_skip_empty = TRUE) {
    // Since we don't really have a value (just some markup we always want to
    // render), let's short-circuit this.
    return FALSE;
  }

  function render($values) {
    return $this->renderValues($values);
  }

  function query() {
    // No-op.
  }
  // @codingStandardsIgnoreEnd
}

class IslandoraQAViewsFieldHandlerTaskActions extends IslandoraQAViewsFieldHandlerActions {
  /**
   * Inherits.
   */
  protected function optionDefinition() {
    $options = parent::optionDefinition();

    $options['action_base_path'] = array(
      'default' => 'islandora_qa/task',
      'translatable' => FALSE,
    );

    return $options;
  }

  /**
   * Inherits.
   */
  protected function getLinks($values) {
    return array(
      array(
        'title' => t('Start Task'),
        'href' => format_string('!base/!task_id', array(
          '!base' => $this->actionBasePath(),
          '!task_id' => $this->getTaskId($values),
        )),
      ),
    );
  }

  /**
   * Get the ID of the Task.
   *
   * @param object $values
   *   All the values to render in the view.
   *
   * @return string|int
   *   The ID of the Task.
   */
  protected function getTaskId($values) {
    return $values -> islandora_qa_task_info_taskid;
  }
}
