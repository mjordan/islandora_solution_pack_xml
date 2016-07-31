<?php

/**
 * @file
 * Class file for islandora_simple_xml_context_condition_namespaces.
 */

/**
 * Matching on the OBJ datastream's namespaces as a condition.
 */
class IslandoraSimpleXmlContextConditionNamespaces extends context_condition {
  /**
   * Override of condition_values().
   */
  // @codingStandardsIgnoreStart
  public function condition_values() {
    return array();
  }
  // @codingStandardsIgnoreEnd

  /**
   * Override of condition_form().
   */
  // @codingStandardsIgnoreStart
  public function condition_form($context) {
    $form = parent::condition_form($context);
    $form['#type'] = 'value';
    $form['#value'] = TRUE;
    return $form;
  }
  // @codingStandardsIgnoreEnd

  /**
   * Override of condition_form_submit().
   */
  // @codingStandardsIgnoreStart
  public function condition_form_submit($values) {
    return array($values);
  }
  // @codingStandardsIgnoreEnd

  /**
   * Override of options_form().
   */
  // @codingStandardsIgnoreStart
  public function options_form($context) {
    $defaults = $this->fetch_from_context($context, 'options');
    return array(
      'islandora_simple_xml_namespaces' => array(
        '#type' => 'textarea',
        '#title' => t('XML namespace URIs to activate this condition'),
        '#description' => t('Set this condition when one of the namepspace URIs in this list is used in the XML OBJ datastream. Enter a list of namespace URIs, separated by spaces. The namespaces can be registered anywhere in the XML documnent, not just in the root element. Matches are case sensitive.'),
        '#default_value' => isset($defaults['islandora_simple_xml_namespaces']) ?
          $defaults['islandora_simple_xml_namespaces'] : '',
      ),
    );
  }
  // @codingStandardsIgnoreEnd

  /**
   * Override of execute().
   */
  public function execute($islandora_object) {
    dd('I have been executed');
    if ($this->condition_used()) {
      foreach ($this->get_contexts() as $context) {
        $config = $this->fetch_from_context($context, 'options');
        $configured_uris_string = $config['islandora_simple_xml_namespaces'];
        $configured_uris = preg_split('/\s+/', $configured_uris_string);
        if (in_array('islandora:sp_simple_xml', $islandora_object->models)) {
          if ($islandora_object['OBJ']) {
            $simple = new SimpleXMLElement($islandora_object['OBJ']->content);
            // Get all the namespaces in the document, including any in
            // child elements.
            $registered_namespaces = $simple->getNamespaces(TRUE);
            dd($registered_namespaces, 'Registered namespaces');
            $uris = array_values($registered_namespaces);
            if (count(array_intersect($uris, $configured_uris))) {
              $this->condition_met($context);
            }
          }
        }
      }
    }
  }

}
