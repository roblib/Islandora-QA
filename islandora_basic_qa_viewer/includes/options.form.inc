<?php

function islandora_basic_qa_viewer_image_viewer_options_form() {
  $form = array();
  
  $form['dsid'] = array(
    '#type' => 'textfield',
    '#title' => t('Data stream'),
    '#size' => 50,
  );
  
  return $form;
}

function islandora_basic_qa_viewer_image_viewer_process_options($params = array()) {
  return $params['values']['dsid'];
}
 
