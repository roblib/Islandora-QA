<?php
/**
 * @file
 * Class implementation for progress field.
 */

class IslandoraQAProgressFieldHandler extends views_handler_field {
  /**
   * Inherits.
   */
  function add_self_tokens(&$tokens, $item) {
    module_load_include('inc', 'islandora_qa', 'includes/db');
    $map = array();
    
    $taskIDs = islandora_qa_get_all_tasks();
    foreach($taskIDs as $id)
    {
      $num = (int)$id->taskId;
      $prog = islandora_qa_get_task_status($num);
      $map[$num] = "$prog[1] done, $prog[2] rejected, $prog[0] to do";
    }
    
    if (isset($tokens['[progress]'])) {
      $tokens['[progress-text]'] = $map[$tokens['[progress]']];
    }
  }

  /**
   * Inherits.
   */
  function document_self_tokens(&$tokens) {
    $tokens['[progress-text]'] = t('A human-readable string representing the progress.');
  }
}
