<?php

/**
 * @file
 * Any hooks/functions used by this module's themes.
 */

/**
 * Implements hook_preprocess_theme().
 */
function islandora_simple_xml_html_viewer_preprocess_islandora_simple_xml_html_viewer(array &$variables) {
  // Get output format as determined by Context, if applicable.
  if (module_exists('islandora_simple_xml_context')) {
    if ($plugin = context_get_plugin('reaction', 'islandora_simple_xml_context_reaction_use_format')) {
      $format = $plugin->execute();
    }
    else {
      $format = variable_get('islandora_solution_pack_xml_output_format', 'full_html');
    }
  }
  else {
    $format = variable_get('islandora_solution_pack_xml_output_format', 'full_html');
  }
  $variables['format'] = $format;

  if (isset($variables['islandora_object'])) {
    $islandora_object = $variables['islandora_object'];
    if ($islandora_object['OBJ']) {
      $variables['islandora_content'] = $islandora_object['OBJ']->content;
    }
  }
}
