<?php

function ISLANDORA_BASIC_QA_VIEWER_MODEL_NAMES() {return array('islandora:sp_large_image_cmodel', 'islandora:sp_pdf', 'islandora:sp_videoCModel', 'islandora:sp-audioCModel');}
function ISLANDORA_BASIC_QA_VIEWER_VIEWER_NAMES(){return array('islandora_large_image_viewers', 'islandora_pdf_viewers', 'islandora_video_viewers', 'islandora_audio_viewers');}


function islandora_qa_get_viewer_name(AbstractObject $object)
{
  $models = $object->models;
  $modelNames = ISLANDORA_BASIC_QA_VIEWER_MODEL_NAMES();
  $viewerNames = ISLANDORA_BASIC_QA_VIEWER_VIEWER_NAMES();
  for($i = 0; $i < count($modelNames) ; $i++)
  {
    if(in_array($modelNames[$i], $models))
      return $viewerNames[$i];
  }
  return null;
}

function islandora_qa_get_viewer_params(AbstractObject $object, $viewerName)
{
  $params = array();

  $viewerNames = ISLANDORA_BASIC_QA_VIEWER_VIEWER_NAMES();

  if($viewerName == 'islandora_large_image_viewers')
  {
    $jp2_url = url("islandora/object/{$object->id}/datastream/JP2/view",
      array(
        'absolute' => TRUE,
      ));
    $params['jp2_url'] = $jp2_url;
  }

  if ($viewerName == 'islandora_pdf_viewers')
  {
    // No parameters needed
  }

  if ($viewerName == 'islandora_video_viewers')
  {
    $params['pid'] = $object->id;
    $params['url'] = url("islandora/object/{$object->id}/datastream/MP4/view");
    $params['tn']  = url("islandora/object/{$object->id}/datastream/TN/view", array('absolute' => TRUE));
    $params['mime'] = 'video/mp4';
  }

  if($viewerName == 'islandora_audio_viewers')
  {
    $params['pid'] = $object->id;
    $params['url'] = url("islandora/object/{$object->id}/datastream/PROXY_MP3/view");
    $params['tn']  = url("islandora/object/{$object->id}/datastream/TN/view", array('absolute' => TRUE));
    $params['mime'] = 'audio/mpeg';
  }

  return $params;
}

function islandora_qa_get_datastream_image(AbstractObject $object, $dsid)
{
  $ds = islandora_datastream_load($dsid, $object);
  if($ds == null)
  {
    return null;
  }
  // if mimetype starts with 'image'
  if(strpos($ds->mimetype, "image") === 0)
  {
    return theme('image', array('path' => 'islandora/object/' .($object -> id). '/datastream/'.$dsid));
  }
  return null;
}

function islandora_qa_get_fallback_image(AbstractObject $object)
{
  $out;
  $DATA_STREAMS = array('MEDIUM_SIZE', 'JPG', 'SAMPLE', 'TN');
  for($i = 0; $i < count($DATA_STREAMS) ; $i++)
  {
    $out = islandora_qa_get_datastream_image($object, $DATA_STREAMS[$i]);
    if($out != null)
    {
      return $out;
    }
  }
  return null;
}

function _islandora_qa_default_viewer ($params = array()){
  module_load_include('inc', 'islandora', 'islandora');
  module_load_include('inc', 'islandora', 'includes/solution_packs');

  $object = $params['object'];

  $viewName = islandora_qa_get_viewer_name($object);

  if($viewName != null)
  {
    $viewerParams = islandora_qa_get_viewer_params($object, $viewName);

    return islandora_get_viewer($viewerParams, $viewName, $object);
  }
  return islandora_qa_get_fallback_image($object);
}


function _islandora_qa_image_viewer ($params = array()){
  $object = $params['object'];
  $dsid = $params['options'];

  $viewer = islandora_qa_get_datastream_image($object, $dsid);
  //return if everything is working
  if($viewer != null){
    return $viewer;
  }

  if(islandora_datastream_load($dsid, $object) != null){
    $viewer = "<p class=\"qa-task-error\">The specified image datastream \"" . $dsid . "\" is not a valid image type</p>";
  }
  else{
    $viewer = "<p class=\"qa-task-error\">The specified image datastream \"" . $dsid . "\" does not exist</p>";
  }

  $fallback = islandora_qa_get_fallback_image($object);

  if($fallback != null){
    $viewer .= $fallback;
  }
  else{
    $viewer = "<p class=\"qa-task-error\">No valid display was found for object \"". $object ."\"</p>";
  }

  return $viewer;

}


function islandora_qa_image_viewer_options_form() {
  $form = array();
  $form['title'] = array(
    '#markup' => '<h2>Options for the Image Datastream Viewer</h2>',
  );
  $form['dsid'] = array(
    '#type' => 'textfield',
    '#title' => t('Datastream ID'),
    '#description' => t('Enter the DSID of a web-friendly image datastream.'),
    '#size' => 50,
  );

  return $form;
}

function islandora_qa_image_viewer_process_options($params = array()) {
  return $params['values']['dsid'];
}

