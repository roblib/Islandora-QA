<?php

function MODEL_NAMES() {return array('islandora:sp_large_image_cmodel', 'foo', 'bar');}
function VIEWER_NAMES(){return array('islandora_large_image_viewers', 'foo', 'bar');}


function islandora_qa_get_viewer_name(AbstractObject $object)
{
  $models = $object->models;
  $modelNames = MODEL_NAMES();
  $viewerNames = VIEWER_NAMES();
  if(in_array($modelNames[0], $models))
    return $viewerNames[0];
  return null;
}

function islandora_qa_get_viewer_params(AbstractObject $object, $viewerName)
{
  $params = array();
  
  $viewerNames = VIEWER_NAMES();
  
  if($viewerName = 'islandora_large_image_viewers')
  {
    $jp2_url = url("islandora/object/{$object->id}/datastream/JP2/view",
        array(
          'absolute' => TRUE,
        ));
    $params['jp2_url'] = $jp2_url;
  }
  
  
  return $params;
}
