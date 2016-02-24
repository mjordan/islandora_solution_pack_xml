<?php

/**
 * @file
 * Any hooks/functions used by this modules theme's.
 */

/**
 * Implements hook_preprocess_theme().
 */
function islandora_simple_xml_viewer_preprocess_islandora_simple_xml(array &$variables) {
  if (isset($variables['fedora_object'])) {
    $islandora_object = $variables['fedora_object'];
    $variables['content'] = htmlspecialchars($islandora_object['OBJ']->content);
  }
}
