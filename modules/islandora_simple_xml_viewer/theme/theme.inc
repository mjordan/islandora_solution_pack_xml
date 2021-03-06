<?php

/**
 * @file
 * Any hooks/functions used by this module's themes.
 */

/**
 * Implements hook_preprocess_theme().
 */
function islandora_simple_xml_viewer_preprocess_islandora_simple_xml_viewer(array &$variables) {
  if (isset($variables['islandora_object'])) {
    $islandora_object = $variables['islandora_object'];
    $variables['islandora_content'] = htmlspecialchars($islandora_object['OBJ']->content);
  }

  if (variable_get('islandora_simple_xml_viewer_prettify', TRUE)) {
    $islandora_object = $variables['islandora_object'];
    $skin = variable_get('islandora_simple_xml_viewer_prettify_skin', '');
    if (strlen($skin)) {
      drupal_add_js('https://cdn.rawgit.com/google/code-prettify/master/loader/run_prettify.js?lang=ml&skin=' .
        $skin, 'external');
    }
    else {
      drupal_add_js('https://cdn.rawgit.com/google/code-prettify/master/loader/run_prettify.js?lang=ml', 'external');
    }
    $variables['islandora_content'] = '<pre class="prettyprint">' . htmlspecialchars($islandora_object['OBJ']->content) . '</pre>';
  }
  else {
    $islandora_object = $variables['islandora_object'];
    $variables['islandora_content'] = '<pre>' . htmlspecialchars($islandora_object['OBJ']->content) . '</pre>';
  }
}
