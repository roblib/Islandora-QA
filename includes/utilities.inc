<?php

function MODEL_NAMES() {return array('islandora:sp_large_image_cmodel', 'islandora:sp_pdf', 'islandora:sp_videoCModel', 'islandora:sp-audioCModel');}
function VIEWER_NAMES(){return array('islandora_large_image_viewers', 'islandora_pdf_viewers', 'islandora_video_viewers', 'islandora_audio_viewers');}


function islandora_qa_get_viewer_name(AbstractObject $object)
{
  $models = $object->models;
  $modelNames = MODEL_NAMES();
  $viewerNames = VIEWER_NAMES();
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
  
  $viewerNames = VIEWER_NAMES();
  
  if($viewerName == 'islandora_large_image_viewers')
  {
    $jp2_url = url("islandora/object/{$object->id}/datastream/JP2/view",
        array(
          'absolute' => TRUE,
        ));
    $params['jp2_url'] = $jp2_url;
  }
  
  if($viewerName == 'islandora_pdf_viewers')
  {
    // No parameters needed
  }
  
  if($viewerName == 'islandora_video_viewers')
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
  $DATA_STREAMS = array('MEDIUM_SIZE', 'SAMPLE', 'TN');
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
