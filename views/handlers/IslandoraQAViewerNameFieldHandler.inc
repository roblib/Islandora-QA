<?php
/**
 * @file
 * Class implementation for status field.
 */

class IslandoraQAViewerNameFieldHandler extends views_handler_field {
  /**
   * Inherits.
   */
  function add_self_tokens(&$tokens, $item) {
    $map = array();
    
    $qa_viewers = module_invoke_all('islandora_qa_viewer_info');
    forEach($qa_viewers as $view)
    {
      $map[$view['callback']] = $view['label'];
    }
    
    if (isset($tokens['[viewer]'])) {
      $tokens['[viewer-text]'] = $map[$tokens['[viewer]']];
    }
  }

  /**
   * Inherits.
   */
  function document_self_tokens(&$tokens) {
    $tokens['[viewer-text]'] = t('A human-readable string representing the viewer.');
  }
  //@codingStandardsIgnoreEnd
}
