<?php

/**
 * @file
 * Any hooks/functions used by this module's themes.
 */

/**
 * Implements hook_preprocess_theme().
 */
function islandora_simple_xml_html_viewer_preprocess_islandora_simple_xml_html_viewer(array &$variables) {
  if (isset($variables['islandora_object'])) {
    $islandora_object = $variables['islandora_object'];
    if ($islandora_object['OBJ']) {
      $variables['islandora_content'] = $islandora_object['OBJ']->content;
    }
  }
}
