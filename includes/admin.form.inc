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

  module_load_include('inc', 'islandora', 'includes/solution_packs');
  $form += islandora_viewers_form('islandora_xml_viewers', 'application/xml');
  return system_settings_form($form);
}
