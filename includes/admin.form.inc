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
  $module_path = drupal_get_path('module', 'islandora_solution_pack_xml');
  $default_tn_path = DRUPAL_ROOT . DIRECTORY_SEPARATOR . $module_path . DIRECTORY_SEPARATOR . 'images' . DIRECTORY_SEPARATOR . 'xml.png';
  if (file_exists(variable_get('islandora_solution_pack_xml_default_thumbnail_path', $default_tn_path))) {
    $tn_exists_markup = '<br /><img src="/misc/watchdog-ok.png" /> File exists.';
  }
  else {
    $tn_exists_markup = '<br /><img src="/misc/watchdog-error.png" /> File does not exist.';
  }
  $form['islandora_solution_pack_xml_default_thumbnail_path'] = array(
    '#title' => t('Path to default thumbnail image'),
    '#type' => 'textfield',
    '#size' => 100,
    '#default_value' => variable_get('islandora_solution_pack_xml_default_thumbnail_path', $default_tn_path),
    '#description' => t('Absolute filesystem path to the default thumbnail image for XML objects. Leave empty to not attach a thumbnail. !tn_exists', array('!tn_exists' => $tn_exists_markup)),
    '#maxlength' => 255,
  );
  $form['islandora_solution_pack_xml_require_obj'] = array(
    '#type' => 'checkbox',
    '#title' => t('Make uploading an OBJ datastream at ingest required?'),
    '#default_value' => variable_get('islandora_solution_pack_xml_require_obj', TRUE),
  );
  $form['islandora_solution_pack_xml_metadata_dsid'] = array(
    '#title' => t('Metadata datastream ID'),
    '#type' => 'textfield',
    '#size' => 20,
    '#default_value' => variable_get('islandora_solution_pack_xml_metadata_dsid', 'MODS'),
    '#description' => t('ID of datastream whose presence triggers display of metadata and description in object display. Leave blank to never display metadata and description.'),
    '#maxlength' => 255,
  );

  $filters = filter_formats();
  $filter_options = array();
  foreach ($filters as $filter) {
    $filter_options[$filter->format] = $filter->name;
  }
  $form['islandora_solution_pack_xml_output_filter'] = array(
    '#type' => 'select',
    '#tilte' => t('Output format'),
    '#options' => $filter_options,
    '#default_value' => variable_get('islandora_solution_pack_xml_output_filter', 'full_html'),
    '#description' => t('The Drupal output filter to apply to HTML rendered by this solution pack.'),
  );

  module_load_include('inc', 'islandora', 'includes/solution_packs');
  $form += islandora_viewers_form('islandora_xml_viewers', NULL, 'islandora:sp_simple_xml');
  return system_settings_form($form);
}
