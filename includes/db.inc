<?php

/**
 * @file
 * Database Helper Functions.
 */

function islandora_qa_get_all_tasks() {
  $result = db_select('islandora_qa_task_info', 'q')
    ->fields('q', array('taskId'))
    ->execute()
    ->fetchAllAssoc('taskId');
  return $result;
}

function islandora_qa_task_exists($taskId) {
  $result = db_select('islandora_qa_task_items', 'q')
    ->fields('q', array('itemId'))
    ->condition('taskId', $taskId)
    ->countQuery()
    ->execute()
    ->fetchField();
  return $result > 0;
}
 
function islandora_qa_get_next_in_task($taskId) {
  $item_id = db_select('islandora_qa_task_items', 'q')
    ->fields('q', array('itemId'))
    ->condition('taskId', $taskId)
    ->condition('status', 0)
    ->execute()
    ->fetchField();
  return $item_id;
}

function islandora_qa_get_progress_in_task($taskId) {
  $done = db_select('islandora_qa_task_items', 'q')
    ->fields('q', array('itemId'))
    ->condition('taskId', $taskId)
    ->condition('status', 0, '!=')
    ->execute()
    ->rowCount();
  $all = db_select('islandora_qa_task_items', 'q')
    ->fields('q', array('itemId'))
    ->condition('taskId', $taskId)
    ->execute()
    ->rowCount();
  return array($done, $all);
}

function islandora_qa_get_task_status($taskId) {
  $notDone = db_select('islandora_qa_task_items', 'q')
    ->fields('q', array('itemId'))
    ->condition('taskId', $taskId)
    ->condition('status', 0, '=')
    ->execute()
    ->rowCount();
  $done = db_select('islandora_qa_task_items', 'q')
    ->fields('q', array('itemId'))
    ->condition('taskId', $taskId)
    ->condition('status', 1, '=')
    ->execute()
    ->rowCount();
  $reject = db_select('islandora_qa_task_items', 'q')
    ->fields('q', array('itemId'))
    ->condition('taskId', $taskId)
    ->condition('status', 2, '=')
    ->execute()
    ->rowCount();
  return array($notDone, $done, $reject);
}

function islandora_qa_get_qa_viewer($taskId) {
  $stream = db_select('islandora_qa_task_info', 'q')
    ->fields('q', array('viewer'))
    ->condition('taskId', $taskId)
    ->execute()
    ->fetchField();
  return $stream;
}

function islandora_qa_get_qa_viewer_options($taskId) {
  $stream = db_select('islandora_qa_task_info', 'q')
    ->fields('q', array('viewerOptions'))
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

function islandora_qa_mark_done_in_task($taskId, $itemId, $user) {
  db_update('islandora_qa_task_items')
    ->fields(array('status' => 1, 'user' => $user))
    ->condition('taskId', $taskId)
    ->condition('itemId', $itemId)
    ->execute();
} 

function islandora_qa_reject_in_task($taskId, $itemId, $reason, $user) {
  db_update('islandora_qa_task_items')
    ->fields(array('status' => 2, 'rejectionReason' => $reason, 'user' => $user))
    ->condition('taskId', $taskId)
    ->condition('itemId', $itemId)
    ->execute();
}

//Rejects item but does not define a user
function islandora_qa_auto_reject_in_task($taskId, $itemId, $reason) {
  db_update('islandora_qa_task_items')
    ->fields(array('status' => 2, 'rejectionReason' => $reason))
    ->condition('taskId', $taskId)
    ->condition('itemId', $itemId)
    ->execute();
}

function islandora_qa_delete_task($taskId) {
    db_delete('islandora_qa_task_info')
      ->condition('taskId', $taskId)
      ->execute();
    db_delete('islandora_qa_task_items')
      ->condition('taskId', $taskId)
      ->execute();
} 
