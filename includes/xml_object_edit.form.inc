<?php

/**
 * @file
 * XML OBJ editing form.
 */

/**
 * Retrives the XML edit form.
 *
 * @param AbstractObject $object
 *   The Islandora object.
 *
 * @return array
 *   The form array.
 */
function islandora_solution_pack_xml_edit_xml(AbstractObject $object) {
  return drupal_get_form('islandora_solution_pack_xml_edit_xml_form', $object);
}

/**
 * Form callback.
 */
function islandora_solution_pack_xml_edit_xml_form($form, &$form_state, AbstractObject $object) {
  $xml = $object['OBJ']->content;
  if ($object['OBJ']->mimetype == 'text/html') {
    $description = t('Edit your HTML here.');
  }
  else {
    $description = t('Edit your XML here. Note that no validation or well-formedness checking is performed on this content.');
  }
  return array(
    'xml' => array(
      '#title' => t('XML OBJ datastream content'),
      '#type' => 'textarea',
      '#rows' => 20,
      '#description' => $description,
      '#default_value' => $xml,
    ),
    'object' => array(
      '#type' => 'value',
      '#value' => $object->id,
    ),
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Save'),
    ),
    'cancel' => array(
      '#markup' => l('Cancel', url('islandora/object/' . $object->id)),
    ),
  );
}

/**
 * From submit function.
 */
function islandora_solution_pack_xml_edit_xml_form_submit($form, &$form_state) {
  $object = islandora_object_load($form_state['values']['object']);
  if (!$object['OBJ']) {
    $xml = $object->constructDatastream('OBJ', 'M');
    $xml->mimetype = 'application/xml';
    $xml->label = 'XML content';
    $xml->setContentFromString($form_state['values']['xml']);
    $object->ingestDatastream($xml);
  }
  else {
    $xml = $object['OBJ'];
    $xml->setContentFromString($form_state['values']['xml']);
  }
  drupal_set_message(t("XML updated for !object.", array('!object' => $object->id)));
  drupal_goto("islandora/object/{$object->id}/manage/datastreams");
}
