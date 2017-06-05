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

  db_insert('islandora_qa_task_info')
      ->fields(array('taskId', 'streamLook', 'streamEdit', 'form'))
      ->values(array(1, 'OBJ', 'MODS', 'mods'))
      ->execute();
      
  db_insert('islandora_qa_task_info')
      ->fields(array('taskId', 'streamLook', 'streamEdit', 'form'))
      ->values(array(2, 'JPEG', 'MODS', 'mods'))
      ->execute();
      
  for( $i = 1; $i<3; $i++ ) {
    for( $j = 1; $j<6; $j++ ) {
      db_insert('islandora_qa_task_items')
          ->fields(array('taskId', 'id'))
          ->values(array($i, $j))
          ->execute();
    }
  }
         
}
