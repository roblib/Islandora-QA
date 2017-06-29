<?php
/**
 * @file
 * islandora_qa.admin.inc
 */

/**
 * Admin from.
 * @return array
 *   Returns admin form.
 */
function islandora_qa_create_form($form, $form_state) {
  $form = array();
  
  $form['dataOne'] = array(
    '#type' => 'textfield',
    '#title' => t('Reference Data stream'),
    '#default_value' => t('MEDIUM_SIZE'),
    '#size' => 15,
  );
  
  $form['dataTwo'] = array(
    '#type' => 'textfield',
    '#title' => t('Editing Data stream'),
    '#default_value' => t('MODS'),
    '#size' => 15,
  );
  
  $form['dataForm'] = array(
    '#type' => 'textfield',
    '#title' => t('Data form'),
    '#default_value' => t('islandora_basic_image_mods_form'),
    '#size' => 50,
  );

  $form['namespace'] = array(
    '#type' => 'textfield',
    '#title' => t('Namespace'),
    '#default_value' => t('islandora'),
    '#size' => 50,
  );

  $form['pidTabs'] = array(
    '#type' => 'vertical_tabs',
  );

  $form['idRange'] = array(
    '#type' => 'fieldset',
    '#title' => t('PID Range'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#group' => 'pidTabs',
  );

  $form['idRange']['numFrom'] = array(
    '#type' => 'textfield',
    '#title' => t('Start Number'),
    '#default_value' => t('7460'),
    '#size' => 10,
  );
  
  $form['idRange']['numTo'] = array(
    '#type' => 'textfield',
    '#title' => t('End Number'),
    '#default_value' => t('7470'),
    '#size' => 10,
  );
  
  $form['idList'] = array(
    '#type' => 'fieldset',
    '#title' => t('PID List'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#group' => 'pidTabs',
  );
  $form['idList']['idField'] = array(
    '#type' => 'textarea',
    '#title' => t('List of PIDs, seperated by commas or newlines.'),
  );

	$form['submit_button'] = array(
		'#type' => 'submit',
		'#value' => t('Submit'),
	);
  return $form;
}

function islandora_qa_create_form_submit($form, $form_state) {
  $nameSpace = $form_state['values']['namespace'];
 
  $rangeStart = (int)$form_state['values']['numFrom'];
  $rangeEnd = (int)$form_state['values']['numTo'];
  //boolean value
  $validRange = $rangeEnd > $rangeStart && ($rangeEnd - $rangeStart) < 10000;
  
  //array of strings
  $otherPIDs = preg_split('/\s*[,\n]\s*/', $form_state['values']['idField'], -1, PREG_SPLIT_NO_EMPTY);
  
  if($validRange || !empty($otherPIDs))
  {
    $taskNum = db_insert('islandora_qa_task_info')
      ->fields(array('streamLook', 'streamEdit', 'form'))
      ->values(array($form_state['values']['dataOne'], $form_state['values']['dataTwo'], $form_state['values']['dataForm']))
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
          ->values(array($taskNum, $nameSpace . ':' . $pid))
          ->execute();
      }
    }
  }
  else
  {
    dpm("The task did not have any valid objects specified and was not created");
  }
         
}
