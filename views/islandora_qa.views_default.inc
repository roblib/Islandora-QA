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
  /* Field: Islandora QA: Stream Look */
  $handler->display->display_options['fields']['streamOne']['id'] = 'streamLook';
  $handler->display->display_options['fields']['streamOne']['table'] = 'islandora_qa_task_info';
  $handler->display->display_options['fields']['streamOne']['field'] = 'streamLook';
  /* Field: Islandora QA: Stream Edit */
  $handler->display->display_options['fields']['streamTwo']['id'] = 'streamEdit';
  $handler->display->display_options['fields']['streamTwo']['table'] = 'islandora_qa_task_info';
  $handler->display->display_options['fields']['streamTwo']['field'] = 'streamEdit';
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

  /* Display: User Set Page */
  $handler = $view->new_display('page', 'User Task Page', 'islandora_qa_task_page');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Your QA Tasks';
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'ingest fedora objects';
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

  $views['islandora_qa_tasks'] = $view;

  return $views;
}
