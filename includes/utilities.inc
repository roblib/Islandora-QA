<?php

function MODEL_NAMES() {return array('islandora:sp_large_image_cmodel', 'islandora:sp_pdf', 'bar');}
function VIEWER_NAMES(){return array('islandora_large_image_viewers', 'islandora_pdf_viewers', 'bar');}


function islandora_qa_get_viewer_name(AbstractObject $object)
{
  $models = $object->models;
  $modelNames = MODEL_NAMES();
  $viewerNames = VIEWER_NAMES();
  for($i = 0; $i < 3 ; $i++)
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
  
  return $params;
}
