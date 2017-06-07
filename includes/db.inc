<?php

/**
 * @file
 * Database Helper Functions.
 */
 
function islandora_qa_get_next_in_task($taskId) {
  $item_id = db_select('islandora_qa_task_items', 'q')
    ->fields('q', array('id'))
    ->condition('taskId', $taskId)
    ->condition('done', 0)
    ->execute()
    ->fetchField();
  return $item_id;
}

function islandora_qa_get_stream_look($taskId) {
  $stream = db_select('islandora_qa_task_info', 'q')
    ->fields('q', array('streamLook'))
    ->condition('taskId', $taskId)
    ->execute()
    ->fetchField();
  return $stream;
}

function islandora_qa_get_stream_edit($taskId) {
  $stream = db_select('islandora_qa_task_info', 'q')
    ->fields('q', array('streamEdit'))
    ->condition('taskId', $taskId)
    ->execute()
    ->fetchField();
  return $stream;
}

function islandora_qa_get_form($taskId) {
  $form = db_select('islandora_qa_task_info', 'q')
    ->fields('q', array('form'))
    ->condition('taskId', $taskId)
    ->execute()
    ->fetchField();
  return $form;
}

function islandora_qa_mark_done_in_task($taskId, $itemId) {
  db_update('islandora_qa_task_items')
    ->fields(array('done' => 1))
    ->condition('taskId', $taskId)
    ->condition('id', $itemId)
    ->execute();
} 
