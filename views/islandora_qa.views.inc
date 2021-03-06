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
        'handler' => 'IslandoraQAProgressFieldHandler',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'viewer' => array(
      'title' => t('Viewer'),
      'help' => t('A viewer that displays information about the current object'),
      'field' => array(
        'handler' => 'IslandoraQAViewerNameFieldHandler',
        'click sortable' => TRUE,
      ),
    ),
    'streamEdit' => array(
      'title' => t('Data Stream'),
      'help' => t('A data stream that is checked during the QA'),
      'field' => array(
        'click sortable' => TRUE,
      ),
    ),
    'form' => array(
      'title' => t('Form'),
      'help' => t('The form that is used to edit the data stream'),
      'field' => array(
        'click sortable' => TRUE,
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
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
      ),
    ),
    'itemId' => array(
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
    'user' => array(
      'title' => t('User ID'),
      'help' => t('ID of the user who created a set.'),
      'field' => array(
        'handler' => 'views_handler_field_user',
        'click sortable' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_user_uid',
        'name field' => 'name',
      ),
      'filter' => array(
        'title' => t('Name'),
        'handler' => 'views_handler_filter_user_name',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'relationship' => array(
        'base' => 'users',
        'base field' => 'uid',
        'handler' => 'views_handler_relationship',
        'label' => t('Set creator'),
        'title' => t('Set Creator'),
        'help' => t('The user who created a given set.'),
      ),
    ),
  );

  return $data;
}
