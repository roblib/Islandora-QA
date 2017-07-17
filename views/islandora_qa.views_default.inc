<?php

/**
 * @file
 * Default views hook.
 */

/**
 * Implements hook_views_default_views().
 */
function islandora_qa_views_default_views() {
  $views = array();

  $view = new view();
  $view->name = 'islandora_qa_tasks';
  $view->description = '';
  $view->tag = 'islandora_qa';
  $view->base_table = 'islandora_qa_task_info';
  $view->human_name = 'Islandora QA Tasks';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Islandora QA Task Sets';
  $handler->display->display_options['css_class'] = 'islandora-qa-tasks-view-table';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'id' => 'id',
    'viewer' => 'viewer',
    'editStream' => 'editStream',
    'form' => 'form',
    'count' => 'count',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'viewer' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'editStream' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'form' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'count' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No sets available.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Field: Islandora QA: Task ID */
  $handler->display->display_options['fields']['id']['id'] = 'taskId';
  $handler->display->display_options['fields']['id']['table'] = 'islandora_qa_task_info';
  $handler->display->display_options['fields']['id']['field'] = 'taskId';
  $handler->display->display_options['fields']['id']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['id']['alter']['path'] = 'islandora_qa/task/[id]';
  $handler->display->display_options['fields']['id']['alter']['target'] = '_blank';
  /* Field: Islandora QA: Viewer */
  $handler->display->display_options['fields']['viewer']['id'] = 'viewer';
  $handler->display->display_options['fields']['viewer']['table'] = 'islandora_qa_task_info';
  $handler->display->display_options['fields']['viewer']['field'] = 'viewer';
  $handler->display->display_options['fields']['viewer']['label'] = 'Viewer';
  $handler->display->display_options['fields']['viewer']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['viewer']['alter']['text'] = '[viewer-text]';
  /* Field: Islandora QA: Stream Edit */
  $handler->display->display_options['fields']['editStream']['id'] = 'streamEdit';
  $handler->display->display_options['fields']['editStream']['table'] = 'islandora_qa_task_info';
  $handler->display->display_options['fields']['editStream']['field'] = 'streamEdit';
  /* Field: Islandora QA: Form */
  $handler->display->display_options['fields']['form']['id'] = 'form';
  $handler->display->display_options['fields']['form']['table'] = 'islandora_qa_task_info';
  $handler->display->display_options['fields']['form']['field'] = 'form';
  /* Field: Islandora QA: Size */
  $handler->display->display_options['fields']['count']['id'] = 'id_1';
  $handler->display->display_options['fields']['count']['table'] = 'islandora_qa_task_items';
  $handler->display->display_options['fields']['count']['field'] = 'taskId';
  $handler->display->display_options['fields']['count']['group_type'] = 'count';
  $handler->display->display_options['fields']['count']['label'] = 'Set Size';
  /* Field: Islandora QA: Task Actions */
  $handler->display->display_options['fields']['actions']['id'] = 'actions';
  $handler->display->display_options['fields']['actions']['table'] = 'islandora_qa_task_info';
  $handler->display->display_options['fields']['actions']['field'] = 'actions';
  $handler->display->display_options['fields']['actions']['label'] = '';
  $handler->display->display_options['fields']['actions']['element_label_colon'] = FALSE;

  /* Display: User Task Page */
  $handler = $view->new_display('page', 'User Task Page', 'islandora_qa_task_page');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Your QA Tasks';
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'islandora qa work on task';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: User: Current */
  $handler->display->display_options['path'] = 'islandora_qa/list/tasks';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Islandora QA Tasks';
  $handler->display->display_options['menu']['description'] = 'List of the current user\'s QA Tasks';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  
  /* Display: Admin Task Page */
  $handler = $view->new_display('page', 'Admin Task Page', 'islandora_qa_task_admin');
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'islandora qa manage task';
  $handler->display->display_options['path'] = 'admin/reports/islandora_qa_tasks';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Islandora QA Tasks';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  $views['islandora_qa_tasks'] = $view;


  //QA Items

  $view = new view();
  $view->name = 'islandora_qa_items';
  $view->description = '';
  $view->tag = 'islandora_qa';
  $view->base_table = 'islandora_qa_task_items';
  $view->human_name = 'Islandora QA Items';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Islandora QA Task Items';
  $handler->display->display_options['css_class'] = 'islandora-qa-tasks-view-table';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'itemId' => 'itemId',
    'taskId' => 'taskId',
    'status' => 'status',
    'reject' => 'reject',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'itemId' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'taskId' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'reject' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No sets available.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Field: Islandora QA: Item ID */
  $handler->display->display_options['fields']['itemId']['id'] = 'itemId';
  $handler->display->display_options['fields']['itemId']['table'] = 'islandora_qa_task_items';
  $handler->display->display_options['fields']['itemId']['field'] = 'itemId';
  $handler->display->display_options['fields']['itemId']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['itemId']['alter']['path'] = 'islandora/object/[itemId]';
  $handler->display->display_options['fields']['itemId']['alter']['target'] = '_blank';
  /* Field: Islandora QA: Task ID */
  $handler->display->display_options['fields']['taskId']['id'] = 'taskId';
  $handler->display->display_options['fields']['taskId']['table'] = 'islandora_qa_task_items';
  $handler->display->display_options['fields']['taskId']['field'] = 'taskId';
  /* Field: Islandora QA: Item Status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'islandora_qa_task_items';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Status';
  $handler->display->display_options['fields']['status']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['status']['alter']['text'] = '[status-text]';
  /* Field: Islandora QA: Reason */
  $handler->display->display_options['fields']['reject']['id'] = 'rejectionReason';
  $handler->display->display_options['fields']['reject']['table'] = 'islandora_qa_task_items';
  $handler->display->display_options['fields']['reject']['field'] = 'rejectionReason';

  /* Display: User Task Page */
  $handler = $view->new_display('page', 'User Task Page', 'islandora_qa_task_page');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Your QA Tasks';
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'islandora qa manage task';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: User: Current */
  $handler->display->display_options['path'] = 'islandora_qa/list/items';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Islandora QA Items';
  $handler->display->display_options['menu']['description'] = 'List of all Task Items';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  
  /* Display: Admin Task Page */
  $handler = $view->new_display('page', 'Admin Task Page', 'islandora_qa_task_admin');
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'islandora qa manage task';
  $handler->display->display_options['path'] = 'admin/reports/islandora_qa_items';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Islandora QA Items';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
 
  $views['islandora_qa_items'] = $view;

  return $views;
}
