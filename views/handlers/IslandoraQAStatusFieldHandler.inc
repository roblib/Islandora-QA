<?php
/**
 * @file
 * Class implementation for status field.
 */

class IslandoraQAStatusFieldHandler extends views_handler_field {
  /**
   * Inherits.
   */
  //@codingStandardsIgnoreStart
  // XXX: Views code uses underscores... Shrug?
  function add_self_tokens(&$tokens, $item) {
    $map = array(
      ISLANDORA_QA_STATUS__NOT_DONE => t('Not Done'),
      ISLANDORA_QA_STATUS__DONE     => t('Done'),
      ISLANDORA_QA_STATUS__REJECTED => t('Rejected'),
    );
    if (isset($tokens['[status]'])) {
      $tokens['[status-text]'] = $map[$tokens['[status]']];
    }
  }

  /**
   * Inherits.
   */
  function document_self_tokens(&$tokens) {
    $tokens['[status-text]'] = t('A human-readable string representing the status.');
  }
  //@codingStandardsIgnoreEnd
}
