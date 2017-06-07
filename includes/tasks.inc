<?php

/**
 * @file
 * Page callbacks and relevant forms (and friends).
 */

/**
 * Map option value back to state number.
 *
 * @param string $value
 *   A value for one of the options dealt with in
 *   islandora_batch_get_mappings().
 * @param array $form_state
 *   The form state, so we can access our "stashed" mapping.
 *
 * @return int
 *   The mapped state number, corresponding to $value.
 */
function islandora_batch_map_value($value, $form_state) {
  return $form_state['stash']['keys'][$value];
}

function islandora_qa_edit_datastream($taskId) {
  module_load_include('inc', 'islandora_qa', 'includes/db');
  
  $object = islandora_object_load(islandora_qa_get_next_in_task($taskId));
  
  $dataStream = islandora_qa_get_stream_edit($taskId);
  
  $form = islandora_qa_get_form($taskId);

  return drupal_get_form('islandora_qa_datastream_form', $taskId, $object, $dataStream, $form);
}

function islandora_qa_datastream_form(array $form, array &$form_state, $taskId, AbstractObject $object, $dsid, $formId) {
  form_load_include($form_state, 'inc', 'xml_form_builder', 'includes/datastream.form');
  
  // Leave this here for legacy reasons.
  $form_state['datastream'] = isset($object[$dsid]) ? $object[$dsid] : FALSE;
  
  $associations = xml_form_builder_datastream_form_get_associations($form_state, $object->models, $dsid);
  //Code to get an association
  //start with a fallback
  $association = xml_form_builder_datastream_form_get_association($form_state, $associations);
  //get an association
  foreach ($associations as $a) {
        if (array_key_exists('id', $a) && $a['id']==$formId) {
            $association = $a;
        }
    }
  

  return isset($association) ?
    islandora_qa_datastream_form_metadata_form($form, $form_state, $taskId, $object, $association) :
    xml_form_builder_datastream_form_select_association_form($form, $form_state, $associations);
}

function islandora_qa_datastream_form_metadata_form(array $form, array &$form_state, $taskId, AbstractObject $object, array $association) {
  $form_state['pid'] = $object->id;
  $form_state['association'] = $association;
  $form_name = $association['form_name'];
  $dsid = $association['dsid'];
  $xml = NULL;
  if (isset($object[$dsid])) {
    $xml = $object[$dsid]->content;
  }
  
  $form = xml_form_builder_get_form($form, $form_state, $form_name, $xml);
  // Make the Object label field required.
  if ($association['title_field']) {
    $title_field_parents = $association['title_field'];
    $title_field_parents[] = '#required';
    drupal_array_set_nested_value($form, $title_field_parents, TRUE);
  }
  
  //TODO Look into other ways to display images
  
  
  $form['container'] = array(
    '#markup' => theme('image', array('path' => 'islandora/object/' .($object -> id). '/datastream/MEDIUM_SIZE', 'attributes' => array())),
  );
  
  $form['taskId'] = array(
		'#type' => 'hidden',
		'#value' => ($taskId),
	);
	
	$form['itemId'] = array(
		'#type' => 'hidden',
		'#value' => ($object -> id),
	);
  
  $form['update'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
    '#name' => 'update',
    '#submit' => array('islandora_qa_datastream_form_metadata_form_submit'),
  );
  return $form;
}
/**
 * Updates the datastream's content with generated xml from the metadata form.
 *
 * Also updates the objects label, and applies a transform to update the DC.
 *
 * @param array $form
 *   The drupal form.
 * @param array $form_state
 *   The drupal form state.
 */
function islandora_qa_datastream_form_metadata_form_submit(array $form, array &$form_state) {
  $object = islandora_object_load($form_state['pid']);
  $association = $form_state['association'];
  $label = NULL;
  if ($association['title_field']) {
    $title_field = drupal_array_get_nested_value($form, $association['title_field']);
    $label = $title_field['#value'];
  }
  $xml_form = new XMLForm($form_state);
  $document = $xml_form->submit($form, $form_state);
  xml_form_builder_update_object($object, $association, $document, $label);
  #$form_state['redirect'] = "islandora/object/{$object->id}";
  islandora_qa_mark_done_in_task($form_state['values']['taskId'], $form_state['values']['itemId']);
}
