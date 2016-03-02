<?php

/**
 * @file
 * Derivative-creation functions.
 */

/**
 * Adds a datastream to an object.
 *
 * @param AbstractObject $object
 *   The object to add a datastream to.
 * @param bool $force
 *   Whether derivative generation is being forced or not.
 *
 * @return array
 *   An array describing the outcome of the thumbnail creation.
 */
function islandora_solution_pack_xml_derivatives_example_create_foo(AbstractObject $object, $force = FALSE) {
  $dsid = 'FOO';
  try {
    $has_ds = isset($object[$dsid]);
    if ($has_ds) {
      $ds = $object[$dsid];
    }
    else {
      $ds = $object->constructDatastream($dsid, 'M');
      $ds->label = $dsid;
      $ds->mimeType = 'application/xml';
      $ds->setContentFromString($object['OBJ']->content);
    }
    if (!$has_ds) {
      $object->ingestDatastream($ds);
    }
    return '';
  }
  catch (exception $e) {
    $variables = array(
      '@ret' => $e->getTraceAsString(),
    );
    watchdog('islandora_solution_pack_xml', 'Failed to add datastream.<br/>Error: @ret', $variables, WATCHDOG_ERROR);
    $message = $e->getMessage();
    return $message;
  }
}
