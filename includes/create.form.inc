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

  $form['namespace'] = array(
    '#type' => 'textfield',
    '#title' => t('Namespace'),
    '#default_value' => t('islandora'),
    '#size' => 50,
  );
  
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

  $form['numFrom'] = array(
    '#type' => 'textfield',
    '#title' => t('Start Number'),
    '#default_value' => t('7460'),
    '#size' => 10,
  );
  
  $form['numTo'] = array(
    '#type' => 'textfield',
    '#title' => t('End Number'),
    '#default_value' => t('7470'),
    '#size' => 10,
  );

	$form['submit_button'] = array(
		'#type' => 'submit',
		'#value' => t('Submit'),
	);
  return $form;
}

function islandora_qa_create_form_submit($form, $form_state) {

  $thing = db_insert('islandora_qa_task_info')
      ->fields(array('streamLook', 'streamEdit', 'form'))
      ->values(array($form_state['values']['dataOne'], $form_state['values']['dataTwo'], $form_state['values']['dataForm']))
      ->execute();
  
  //TODO Clean this
  // dpm will display a message that contains only the taskID
  // This code is used only to get the taskID into a variable
  $taskNum = dpm($thing);
  
  $start = (int)$form_state['values']['numFrom'];
  $end = (int)$form_state['values']['numTo'];
  $nameSpace = $form_state['values']['namespace'];
  
  //if the end is after the start, but still less than 10000.
  if($end > $start && ($end - $start) < 10000 )
  {
    for( $i = $start; $i <= $end; $i++ ) {
      db_insert('islandora_qa_task_items')
          ->fields(array('taskId', 'itemId'))
          ->values(array($taskNum, $nameSpace . ':' . $i))
          ->execute();
    }
  }
         
}
