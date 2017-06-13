<?php
/**
 * @file
 * Views hook implementations.
 */

/**
 * Implements hook_views_data().
 */
function islandora_qa_views_data() {
  $data = array();

  $data['islandora_qa_task_info'] = array(
    'table' => array(
      'group' => t('Islandora QA'),
      'base' => array(
        'field' => 'id',
        'title' => t('Islandora QA Tasks'),
        'help' => t('A set of QA Tasks'),
      ),
    ),
    'taskId' => array(
      'title' => t('Task ID'),
      'help' => t('ID of the task set'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'streamLook' => array(
      'title' => t('First Data Stream'),
      'help' => t('The data stream used to provide information for editing'),
      'field' => array(
        'click sortable' => TRUE,
      ),
    ),
    'streamEdit' => array(
      'title' => t('Second Data Stream'),
      'help' => t('The data stream that is checked during the QA'),
      'field' => array(
        'click sortable' => TRUE,
      ),
    ),
    'form' => array(
      'title' => t('Form'),
      'help' => t('The form that is used to edit the second data stream'),
      'field' => array(
        'click sortable' => TRUE,
      ),
    ),
    'actions' => array(
      'title' => t('Task Actions'),
      'help' => t('A list of actions which may be performed on an item in the queue.'),
      'field' => array(
        'handler' => 'IslandoraQaViewsFieldHandlerTaskActions',
      ),
    ),
  );

  $data['islandora_qa_task_items'] = array(
    'table' => array(
      'group' => t('Islandora QA'),
      'base' => array(
        'field' => 'id',
        'title' => t('Islandora QA Task items'),
        'help' => t('A set of QA Task items'),
      ),
      'join' => array(
        'islandora_qa_task_info' => array(
          'left_field' => 'taskId',
          'field' => 'taskId',
        ),
      ),
    ),
    'taskId' => array(
      'title' => t('Task ID'),
      'help' => t('ID of the task set'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'id' => array(
      'title' => t('Item ID'),
      'help' => t('ID of an item in the set'),
      'field' => array(
        'click sortable' => TRUE,
      ),
    ),
    'status' => array(
      'title' => t('Status'),
      'help' => t('If the item has been successfully processed'),
      'field' => array(
        'handler' => 'IslandoraQAStatusFieldHandler',
        #'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'rejectionReason' => array(
      'title' => t('Rejection Reason'),
      'help' => t('The reason the item was rejected'),
      'field' => array(
        'click sortable' => TRUE,
      ),
    ),
  );

  return $data;
}
