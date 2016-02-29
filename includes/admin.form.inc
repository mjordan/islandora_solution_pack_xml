<?php

/**
 * @file
 * Handles the display/submission of the admin settings form for this module.
 */

/**
 * Defines the admin settings form.
 *
 * @param array $form
 *   The Drupal form definition.
 * @param array $form_state
 *   The Drupal form state.
 *
 * @return array
 *   The Drupal form definition.
 */
function islandora_solution_pack_xml_admin(array $form, array &$form_state) {
  $form['islandora_solution_pack_xml_allow_render_stylesheet_upload'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow users to upload object-specific XSLT stylesheet for rendering OBJ files?'),
    '#description' => t('If present, this stylesheet will override collection-level stylesheets'),
    '#default_value' => variable_get('islandora_solution_pack_xml_allow_render_stylesheet_upload', TRUE),
  );
  $form['islandora_solution_pack_xml_allow_thumbnail_upload'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow users to upload object-specific thumbnails?'),
    '#default_value' => variable_get('islandora_solution_pack_xml_allow_thumbnail_upload', TRUE),
  );
  $module_path = drupal_get_path('module', 'islandora_solution_pack_xml');
  $default_tn_path = DRUPAL_ROOT . DIRECTORY_SEPARATOR . $module_path . DIRECTORY_SEPARATOR . 'images' . DIRECTORY_SEPARATOR . 'xml.png';
  if (file_exists(variable_get('islandora_solution_pack_xml_default_thumbnail_path', $default_tn_path))) {
    $tn_exists_markup = '<br /><img src="http://localhost:8000/misc/watchdog-ok.png" /> File exists.';
  }
  else {
    $tn_exists_markup = '<br /><img src="http://localhost:8000/misc/watchdog-error.png" /> File does not exist.';
  }
  $form['islandora_solution_pack_xml_default_thumbnail_path'] = array(
    '#title' => t('Path to default thumbnail image'),
    '#type' => 'textfield',
    '#size' => 100,
    '#default_value' => variable_get('islandora_solution_pack_xml_default_thumbnail_path', $default_tn_path),
    '#description' => t('Absolute filesystem path to the default thumbnail image for XML objects. Leave empty to not attach a thumbnail. !tn_exists', array('!tn_exists' => $tn_exists_markup)),
    '#maxlength' => 255,
  );

  module_load_include('inc', 'islandora', 'includes/solution_packs');
  $form += islandora_viewers_form('islandora_xml_viewers', 'application/xml');
  return system_settings_form($form);
}
