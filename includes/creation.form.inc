<?php

function islandora_qa_task_creation_form ($form, &$form_state, $management = FALSE) {
  if (!isset($form_state['stage'])) $form_state['stage'] = 'one';
  if (!isset($form_state['management'])) $form_state['management'] = $management;
  
  $form = array();
  
  switch ($form_state['stage']) {
    case 'one':
      return islandora_qa_task_creation_page_one_form($form, $form_state);
    case 'two': 
      return islandora_qa_task_creation_page_two_form($form, $form_state);  
  }
   
  return $form;
}

function islandora_qa_task_creation_page_one_form($form, &$form_state){
  module_load_include('inc', 'xml_form_builder', 'includes/associations');

  $form['#title'] = t('Create a new QA Tasklist (queue).');

  $form['chooseObjects'] = array(
    '#type' => 'fieldset',
    '#title' => t('Select objects'),
    '#description' => t('Populate the queue with islandora objects, by PID.'),
  );
  $form['chooseObjects']['pidTabs'] = array(
    '#type' => 'vertical_tabs',
    '#default_tab' => 'id_list',
  );

  $form['id_list'] = array(
    '#type' => 'fieldset',
    '#title' => t('PID List'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#group' => 'pidTabs',
  );
  $form['id_list']['idField'] = array(
    '#type' => 'textarea',
    '#description' => t('List of PIDs, separated by commas or newlines.'),
  );

  $form['id_range'] = array(
    '#type' => 'fieldset',
    '#title' => t('PID Range'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#group' => 'pidTabs',
    '#description' => t('Select objects that fall into a numeric range of PIDs in a single namespace.'),
  );

  $form['id_range']['namespace'] = array(
    '#type' => 'textfield',
    '#title' => t('Namespace'),
    '#default_value' => t('islandora'),
    '#size' => 50,
  );

  $form['id_range']['num_from'] = array(
    '#type' => 'textfield',
    '#title' => t('Start Number'),
    '#size' => 10,
  );
  
  $form['id_range']['num_to'] = array(
    '#type' => 'textfield',
    '#title' => t('End Number'),
    '#size' => 10,
  );
  
  $model = (isset($form_state['values']['model']))? $form_state['values']['model'] : 'any';
  $models = ($model == 'any')? array() : array($model);
  
  $ds = (isset($form_state['values']['datastream']))? $form_state['values']['datastream'] : 'any';
  $DSIDs = ($ds == 'any')? array() : array($ds);
  
  $xml_forms = xml_form_builder_get_associations(array(), $models, $DSIDs);
  foreach($xml_forms as $f)
  {
    $key = $f['id'].':'.$f['dsid'];
    $form_options[$key] = $f['form_name'];
  }
  
  $model_options['any'] = 'any';
  $dsid_options['any'] = 'any';
  $all_xml_forms = xml_form_builder_get_associations();

  foreach($all_xml_forms as $f)
  {
    $key = $f['dsid'];
    if(!isset($dsid_options[$key]))
      $dsid_options[$key] = $key;
    $key = $f['content_model'];
    if(!isset($model_options[$key]))
      $model_options[$key] = $key;
  }
  
  $form['xml_form_group'] = array(
    '#type' => 'fieldset',
    '#title' => t('Select a Metadata Form'),
    '#description' => t('Select the metadata form. This uses configured Islandora form associations.'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
);

  $form['xml_form_group']['filters'] = array(
    '#type' => 'fieldset',
    '#title' => t('Filters'),
  );
  $form['xml_form_group']['filters']['datastream'] = array(
    '#type' => 'select',
    '#title' => t('Filter forms by datastream'),
    '#options' => $dsid_options,
    '#default' => 'any',
    '#ajax' => array(
      'callback' => 'islandora_qa_ajax_callback',
      'wrapper' => 'radios-div',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  
  $form['xml_form_group']['filters']['model'] = array(
    '#type' => 'select',
    '#title' => t('Filter forms by content model'),
    '#options' => $model_options,
    '#default' => 'any',
    '#ajax' => array(
      'callback' => 'islandora_qa_ajax_callback',
      'wrapper' => 'radios-div',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  
  $form['xml_form_group']['xml_form'] = array(
    '#type' => 'radios',
    '#prefix' => '<div id="radios-div">',
    '#suffix' => '</div>',
    '#options' => $form_options,
  );
  
  $qa_viewers = module_invoke_all('islandora_qa_viewer_info');
  foreach($qa_viewers as $v)
  {
    $viewers[$v['callback']] = $v['label'] . ' - ' . $v['description'];
  }
  
  $form['viewer'] = array(
    '#type' => 'radios',
    '#title' => t('Select a Viewer'),
    '#description' => t('If the selected viewer has options, they will be presented on the next page.'),
    '#options' => $viewers,
  );

	$form['next'] = array(
		'#type' => 'submit',
		'#value' => t('Next'),
	);
  return $form;
}

function islandora_qa_task_creation_page_two_form($form, &$form_state){
  $qa_viewer = $form_state['multistep_values']['one']['viewer'];
  
  $params = array('function' => 'options');
  
  $form = $qa_viewer($params);
  
  if($form == null) {
    $form['message'] = array(
		  '#markup' => 'The selected viewer has no options.<br/>',
	  );
  }
  
  $form['back'] = array(
		'#type' => 'submit',
		'#value' => t('Back'),
	);
  
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Submit'),
	);
  
  return $form;
}

function islandora_qa_task_creation_form_validate ($form, &$form_state) {
  switch ($form_state['triggering_element']['#value']) {
    case 'Next':
      return islandora_qa_task_creation_validate_page_one($form, $form_state);
    case 'Submit':
      return islandora_qa_task_creation_validate_page_two($form, $form_state);
  }
  
  return;
}

function islandora_qa_task_creation_form_submit ($form, &$form_state) {
  switch ($form_state['triggering_element']['#value']) {
    case 'Next':
      $form_state['multistep_values'][$form_state['stage']] = $form_state['values'];
      $form_state['stage'] = 'two';
      break;
    case 'Back':
      $form_state['stage'] = 'one';
      break;
    case 'Submit':
      $form_state['multistep_values'][$form_state['stage']] = $form_state['values'];
      $form_state['stage'] = 'one';
      islandora_qa_process_creation_form($form, $form_state);
      break;
  }
  
  if (isset($form_state['multistep_values']['form_build_id'])) {
    $form_state['values']['form_build_id'] = $form_state['multistep_values']['form_build_id'];
  }
  $form_state['multistep_values']['form_build_id'] = $form_state['values']['form_build_id'];
  
  $form_state['rebuild'] = TRUE;
}

function islandora_qa_process_creation_form($form, &$form_state){
  $nameSpace = $form_state['multistep_values']['one']['namespace'];
 
  $rangeStart = (int)$form_state['multistep_values']['one']['num_from'];
  $rangeEnd = (int)$form_state['multistep_values']['one']['num_to'];
  //boolean value
  $validRange = $rangeEnd > $rangeStart && ($rangeEnd - $rangeStart) < 10000;
  
  $PIDs = preg_split('/\s*[,\n]\s*/', $form_state['multistep_values']['one']['idField'], -1, PREG_SPLIT_NO_EMPTY);
  
  if($validRange)
  {
    for( $i = $rangeStart; $i <= $rangeEnd; $i++ ) {
      $PIDs[] = $nameSpace . ':' . $i;
    }
  }
  
  $PIDs = array_unique($PIDs);
  
  $xml_form = explode(':', $form_state['multistep_values']['one']['xml_form']);
  $editForm = $xml_form[0];
  $editDS = $xml_form[1];
  
  $viewer = $form_state['multistep_values']['one']['viewer'];
  
  $params = array(
    'function' => 'process',
    'values' => $form_state['multistep_values']['two'],
  );
  
  $options = $viewer($params);

  $taskNum = db_insert('islandora_qa_task_info')
    ->fields(array('viewer', 'viewerOptions', 'streamEdit', 'form'))
    ->values(array($viewer, $options, $editDS, $editForm))
    ->execute();

  foreach($PIDs as $pid){
    db_insert('islandora_qa_task_items')
      ->fields(array('taskId', 'itemId'))
      ->values(array($taskNum, $pid))
      ->execute();
  }
  $message = "Task " . $taskNum . " was created";
  drupal_set_message($message);
  
  drupal_goto($form_state['management'] ? 'admin/reports/islandora_qa_tasks' : 'islandora_qa/list/tasks');
}

function islandora_qa_task_creation_validate_page_one($form, &$form_state) {
  $MAX_RANGE = 10000;

  $rangeStart = (int)$form_state['values']['num_from'];
  $rangeEnd = (int)$form_state['values']['num_to'];

  if($rangeEnd - $rangeStart >= $MAX_RANGE)
    form_set_error('range_limit', 'The specified range of pids can not be larger than ' . ($MAX_RANGE -1));

  //boolean value
  $validRange = $rangeEnd > $rangeStart && ($rangeEnd - $rangeStart) < $MAX_RANGE;
  
  //array of strings
  $otherPIDs = preg_split('/\s*[,\n]\s*/', $form_state['values']['idField'], -1, PREG_SPLIT_NO_EMPTY);
  
  if(!$validRange && empty($otherPIDs))
    form_set_error('no_pids', 'No Islandora objects have been specified for the task');
}

function islandora_qa_task_creation_validate_page_two($form, &$form_state) {

}

function islandora_qa_ajax_callback($form, $form_state) {
  return $form['xml_form_group']['xml_form'];
}
