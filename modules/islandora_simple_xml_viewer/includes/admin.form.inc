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
    '#title' => t('Prettify'),
    '#description' => t('Prettify the XML markup with <a href="https://github.com/google/code-prettify">' .
      'Google Javascript code prettifier</a>.'),
    '#default_value' => variable_get('islandora_simple_xml_viewer_prettify', TRUE),
  );
  $form['islandora_simple_xml_viewer_prettify_skin'] = array(
    '#title' => t('Skin'),
    '#type' => 'textfield',
    '#size' => 20,
    '#default_value' => variable_get('islandora_simple_xml_viewer_prettify_skin', ''),
    '#description' => t('See the <a href="https://rawgit.com/google/code-prettify/master/styles/index.html">' .
      'skin gallery</a> for examples. Enter one of "desert", "sunburst", "doxy", etc. here. Leave blank' .
      ' for default.'),
    '#maxlength' => 50,
  );

  return system_settings_form($form);
}
