<?php

/**
 * @file
 * This file contains all theme and preprocess functions.
 */

/**
 * Prepares variables for islandora-simple-xml templates.
 *
 * Default template: islandora-simple-xml.tpl.php.
 *
 * @param array $variables
 *   An associative array containing:
 *   - islandora_object: An AbstractObject from Islandora.
 */
function islandora_solution_pack_xml_preprocess_islandora_solution_pack_xml_default(array &$variables) {
  drupal_add_js('misc/form.js');
  drupal_add_js('misc/collapse.js');
  module_load_include('inc', 'islandora', 'includes/datastream');
  module_load_include('inc', 'islandora', 'includes/utilities');
  module_load_include('inc', 'islandora', 'includes/metadata');

  $islandora_object = $variables['islandora_object'];

  // We should eventually remove the DC object and dc_array code as it only
  // exists to not break legacy implementations.
  try {
    if (isset($islandora_object['DC']) && islandora_datastream_access(ISLANDORA_VIEW_OBJECTS, $islandora_object['DC'])) {
      $dc = $islandora_object['DC']->content;
      $dc_object = DublinCore::importFromXMLString($dc);
    }
  }
  catch (Exception $e) {
    drupal_set_message(t('Error retrieving object %s %t', array('%s' => $islandora_object->id, '%t' => $e->getMessage())), 'error', FALSE);
  }
  $variables['islandora_dublin_core'] = isset($dc_object) ? $dc_object : NULL;
  $variables['dc_array'] = isset($dc_object) ? $dc_object->asArray() : array();
  $variables['islandora_object_label'] = $islandora_object->label;
  $variables['theme_hook_suggestions'][] = 'islandora_simple_xml__' . str_replace(':', '_', $islandora_object->id);
  $variables['parent_collections'] = islandora_get_parents_from_rels_ext($islandora_object);
  $metadata_dsid = variable_get('islandora_solution_pack_xml_metadata_dsid', 'MODS');
  if ($islandora_object[$metadata_dsid]) {
    $variables['metadata'] = islandora_retrieve_metadata_markup($islandora_object);
    $variables['description'] = islandora_retrieve_description_markup($islandora_object);
  }
  else {
    $variables['metadata'] = '';
    $variables['description'] = '';
  }

  $obj_xml_content = $islandora_object['OBJ']->content;

  if ($islandora_object['RENDER_STYLESHEET']) {
    module_load_include('inc', 'islandora_solution_pack_xml', 'includes/utilities');
    $object_render_stylesheet = $islandora_object['RENDER_STYLESHEET']->content;
    $variables['islandora_content'] = islandora_solution_pack_xml_apply_xslt($object_render_stylesheet, $obj_xml_content);
  }
  // If the object is a member of a collection that has a RENDER_STYLESHEET ds,
  // use that stylesheet. But only do that if the object is a member of one
  // collection.
  elseif (count($variables['parent_collections']) == 1 &&
    $variables['parent_collections'][0]['RENDER_STYLESHEET']) {
    module_load_include('inc', 'islandora_solution_pack_xml', 'includes/utilities');
    $object_render_stylesheet = $variables['parent_collections'][0]['RENDER_STYLESHEET']->content;
    $variables['islandora_content'] = islandora_solution_pack_xml_apply_xslt($object_render_stylesheet, $obj_xml_content);
  }
  else {
    $variables['islandora_content'] = '<pre>' . htmlspecialchars($obj_xml_content) . '</pre>';
  }

  module_load_include('inc', 'islandora', 'includes/solution_packs');
  $viewer = islandora_get_viewer(array(), 'islandora_xml_viewers', $islandora_object);
  // Viewers defined by islandora_simple_xml_context override the
  // system default.
  if (module_exists('islandora_simple_xml_context')) {
    if ($plugin = context_get_plugin('reaction', 'islandora_simple_xml_context_reaction_use_viewer')) {
      $viewer = $plugin->execute($islandora_object);
    }
  }

  if ($viewer) {
    $variables['islandora_content'] = $viewer;
  }
}
