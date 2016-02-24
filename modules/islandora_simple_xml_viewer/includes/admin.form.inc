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
function islandora_simple_xml_viewer_admin(array $form, array &$form_state) {
  $form['islandora_simple_xml_viewer_prettify'] = array(
    '#type' => 'checkbox',
    '#title' => t('Prettify '),
    '#description' => t('Prettify the XML markup with Google Javascript code prettifier.'),
    '#default_value' => variable_get('islandora_simple_xml_viewer_prettify', TRUE),
  );

  return system_settings_form($form);
}
