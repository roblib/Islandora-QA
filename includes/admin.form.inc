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
function islandora_qa_admin_form($form, $form_state) {
  $form = array();

	$form['submit_button'] = array(
		'#type' => 'submit',
		'#value' => t('Click Here!'),
	);
  return $form;
}
