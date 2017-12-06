<?php

/**
 * @file
 * API file demonstrating hooks used by islandora_qa.
 */

/**
 * Hook to register viewers.
 *
 * @return array
 *   An associative array mapping unique machine names to associative arrays
 *   containing the following keys:
 *   - label: A translated, human-readable title
 *   - callback: A string containing the name of the callback function.
 *   - description: A translated more detailed description.
 */
function hook_islandora_qa_viewer_info() {
  return array(
    'super_viewer' => array(
      'label' => t('Super Duper Viewer'),
      'callback' => 'super_duper_viewer_callback',
      'description' => t('displays the thumbnail (TN) datastream.')
    ),
  );

}