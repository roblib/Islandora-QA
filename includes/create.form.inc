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

	$form['submit_button'] = array(
		'#type' => 'submit',
		'#value' => t('Click Here!'),
	);
  return $form;
}

function islandora_qa_create_form_submit($form, $form_state) {

  $thing = db_insert('islandora_qa_task_info')
      ->fields(array('streamLook', 'streamEdit', 'form'))
      ->values(array('OBJ', 'MODS', 'mods'))
      ->execute();
  
  //TODO Clean this
  // dpm will display a message that contains only the taskID
  // This code is used only to get the taskID into a variable
  $num = dpm($thing);
      
  for( $j = 7460; $j<7470; $j++ ) {
    db_insert('islandora_qa_task_items')
        ->fields(array('taskId', 'id'))
        ->values(array($num, $j))
        ->execute();
  }
         
}
