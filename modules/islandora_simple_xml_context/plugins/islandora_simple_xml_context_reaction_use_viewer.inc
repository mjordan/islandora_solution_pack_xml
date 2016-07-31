<?php
/**
 * @file
 * Context plugin that retrieves a rendered viewer.
 */

/**
 * Expose a message as a context reaction.
 */
class IslandoraSimpleXmlContextReactionUseViewer extends context_reaction {

  /**
   * Allow the admin to define some text to display.
   *
   * @param string $context
   *   The context as passed from context module.
   *
   * @return array
   *   The FAPI array as read by context module.
   */
  // @codingStandardsIgnoreStart
  function options_form($context) {
    $settings = $this->fetch_from_context($context);
    module_load_include('inc', 'islandora', 'includes/solution_packs');
    $options = array();
    if ($viewers = islandora_get_viewers(array('application/xml'), 'islandora:sp_simple_xml')) {
      foreach ($viewers as $key => $properties) {
        $options[$key] = $properties['label'];
      }
    }
    else {
      $options = array('' => t("No viewers are available for the Simple XML Content Model"));
    }
    $form = array(
      '#title' => t('Islandora Simple XML Viewers'),
      'islandora_simple_xml_viewers' => array(
        '#title' => t('Islandora Simple XML Viewers'),
        '#description' => t('Choose the name of the viewer to use when reaction is active.'),
        '#type' => 'select',
        '#options' => $options,
        '#default_value' => isset($settings['islandora_simple_xml_viewers']) ? $settings['islandora_simple_xml_viewers'] : '',
      ),
    );
    return $form;
  }
  // @codingStandardsIgnoreEnd

  /**
   * Pass the rendered viewer output to the theme preprocess function.
   */
  public function execute($object) {
    foreach ($this->get_contexts() as $context) {
      if ($context->reactions['islandora_simple_xml_context_reaction_use_viewer']['islandora_simple_xml_viewers']) {
        module_load_include('inc', 'islandora', 'includes/solution_packs');
        $viewer_id = $context->reactions['islandora_simple_xml_context_reaction_use_viewer']['islandora_simple_xml_viewers'];
        $callback = islandora_get_viewer_callback($viewer_id);
        if (function_exists($callback)) {
          // @todo: How do we pass viewer params into the 'execute()' function?
          $params = array();
          return $callback($params, $object);
        }
      }
    }
  }

}
