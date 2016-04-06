<?php

/**
 * @file
 * Class file for islandora_simple_xml_context_condition_root_element.
 */

/**
 * Matching on the OBJ datastream's root element as a condition.
 */
class IslandoraSimpleXmlContextConditionRootElement extends context_condition {
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
      'islandora_simple_xml_root_elements' => array(
        '#type' => 'textarea',
        '#title' => t('XML root elements to activate this condition'),
        '#description' => t('Set this condition when one or more of the root elements in this list is present in the XML OBJ datastream. Enter a list of root element names (no attributes or markup), separated by spaces. Matching is case sensitive.'),
        '#default_value' => isset($defaults['islandora_simple_xml_root_elements']) ?
          $defaults['islandora_simple_xml_root_elements'] : '',
      ),
    );
  }
  // @codingStandardsIgnoreEnd

  /**
   * Override of execute().
   */
  public function execute($islandora_object) {
    if ($this->condition_used()) {
      foreach ($this->get_contexts() as $context) {
        $config = $this->fetch_from_context($context, 'options');
        $root_elements_string = $config['islandora_simple_xml_root_elements'];
        $root_elements = preg_split('/\s+/', $root_elements_string);
        if (in_array('islandora:sp_simple_xml', $islandora_object->models)) {
          if ($islandora_object['OBJ']) {
            $dom = new DomDocument();
            $dom->loadXML($islandora_object['OBJ']->content);
            $root_element = $dom->documentElement;
            if (in_array($root_element->nodeName, $root_elements)) {
              $this->condition_met($context);
            }
          }
        }
      }
    }
  }

}
