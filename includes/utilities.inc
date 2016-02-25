<?php

/**
 * @file
 * Utility functions.
 */

/**
 * Applies an XSLT transform to an XML string.
 *
 * @param string $xslt
 *   An XSLT stylesheet.
 * @param string $input_xml
 *   An XML string.
 *
 * @return string
 *   The transformed XML.
 */
function islandora_solution_pack_xml_apply_xslt($xslt, $input_xml) {
  try {
    $xsl_doc = new DOMDocument();
    $xsl_doc->loadXML($xslt);
    $xml_doc = new DOMDocument();
    $xml_doc->loadXML($input_xml);
    $xslt_proc = new XSLTProcessor();
    $xslt_proc->importStylesheet($xsl_doc);
    $output_xml = $xslt_proc->transformToXML($xml_doc);
    return $output_xml;
  }
  catch (exception $e) {
    $success = array(
      'success' => FALSE,
      'messages' => array(
        array(
          'message' => t('Failed to apply XSL transform.'),
          'type' => 'watchdog',
          'severity' => WATCHDOG_ERROR,
        ),
      ),
    );
  }
}
