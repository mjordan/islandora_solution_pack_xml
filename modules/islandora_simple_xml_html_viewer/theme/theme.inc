<?php

/**
 * @file
 * Any hooks/functions used by this module's themes.
 */

/**
 * Implements hook_preprocess_theme().
 */
function islandora_simple_xml_html_viewer_preprocess_islandora_simple_xml_html_viewer(array &$variables) {
  $filter = variable_get('islandora_solution_pack_xml_output_filter', 'full_html');
  if (isset($variables['islandora_object'])) {
    $islandora_object = $variables['islandora_object'];
    if ($islandora_object['OBJ']) {
      $variables['islandora_content'] = check_markup($islandora_object['OBJ']->content, $filter);
    }
  }
}
