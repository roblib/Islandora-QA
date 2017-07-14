<?php

function islandora_qa_task_creation_form ($form, &$form_state) {
  if (!isset($form_state['stage'])) $form_state['stage'] = 'one';
  
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
  $form['pidTabs'] = array(
    '#type' => 'vertical_tabs',
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
    '#title' => t('List of PIDs, seperated by commas or newlines.'),
  );

  $form['id_range'] = array(
    '#type' => 'fieldset',
    '#title' => t('PID Range'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#group' => 'pidTabs',
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
  
  $form['edit_datastream'] = array(
    '#type' => 'textfield',
    '#title' => t('Editing Data stream'),
    '#default_value' => t('MODS'),
    '#size' => 15,
  );
  
  $form['edit_datastream_form'] = array(
    '#type' => 'textfield',
    '#title' => t('Data form'),
    '#size' => 50,
  );
  
  $qa_viewers = module_invoke_all('islandora_qa_viewer_info');
  forEach($qa_viewers as $view)
  {
    $viewers[$view['callback']] = $view['label'];
  }
  
  $form['viewer'] = array(
    '#type' => 'radios',
    '#options' => $viewers,
    '#default_value' => 1,
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
  
  //array of strings
  $otherPIDs = preg_split('/\s*[,\n]\s*/', $form_state['multistep_values']['one']['idField'], -1, PREG_SPLIT_NO_EMPTY);
  
  $editDS = $form_state['multistep_values']['one']['edit_datastream'];
  $editForm = $form_state['multistep_values']['one']['edit_datastream_form'];
  
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
  dpm("Task " . $taskNum . " was created");
    
  if($validRange)
  {
    for( $i = $rangeStart; $i <= $rangeEnd; $i++ ) {
      db_insert('islandora_qa_task_items')
        ->fields(array('taskId', 'itemId'))
        ->values(array($taskNum, $nameSpace . ':' . $i))
        ->execute();
    }
  }
  if(!empty($otherPIDs))
  {
    foreach($otherPIDs as $pid){
      db_insert('islandora_qa_task_items')
        ->fields(array('taskId', 'itemId'))
        ->values(array($taskNum, $pid))
        ->execute();
    }
  }
}

function islandora_qa_task_creation_validate_page_one($form, &$form_state) {
  $rangeStart = (int)$form_state['values']['num_from'];
  $rangeEnd = (int)$form_state['values']['num_to'];
  //boolean value
  $validRange = $rangeEnd > $rangeStart && ($rangeEnd - $rangeStart) < 10000;
  
  //array of strings
  $otherPIDs = preg_split('/\s*[,\n]\s*/', $form_state['values']['idField'], -1, PREG_SPLIT_NO_EMPTY);
  
  if(!$validRange && empty($otherPIDs))
    form_set_error('no_pids', 'No Islandora objects have been specified for the task');
}

function islandora_qa_task_creation_validate_page_two($form, &$form_state) {

}
