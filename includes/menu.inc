<?php

/**
 * Menu page callback, to delete a task.
 */
function islandora_qa_delete_task_page_callback($id, $management = FALSE) {
  return drupal_get_form('islandora_qa_delete_task_form', $id, $management);
}

/**
 * Form building function, to delete a task.
 */
function islandora_qa_delete_task_form($form, &$form_state, $id, $management) {
  form_load_include($form_state, 'inc', 'islandora_qa', 'includes/menu');
  return confirm_form(
    $form,
    t('Are you sure you want to delete task @num?', array(
      '@num' => $id,
    )),
    $management ? "admin/reports/islandora_qa_items/$id" : "islandora_qa/list/items/$id",
    t('This will delete the task. Islandora objects that were a part of the task will be unaffected')
  );
}

/**
 * Form submission handler, to delete a task.
 */
function islandora_qa_delete_task_form_submit(&$form, &$form_state) {
  module_load_include('inc', 'islandora_qa', 'includes/db');
  list($id, $management) = $form_state['build_info']['args'];
  islandora_qa_delete_task($id);
  $form_state['redirect'] = array(
    $management ? 'admin/reports/islandora_qa_items' : 'islandora_qa/list/items',
  );
  drupal_set_message(t("Task has been deleted"));
}
