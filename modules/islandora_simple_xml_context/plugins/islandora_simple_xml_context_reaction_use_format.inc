<?php
/**
 * @file
 * Context plugin that registers a text format within an Islandora Simple XML viewer.
 */

/**
 * Expose a message as a context reaction.
 */
class IslandoraSimpleXmlContextReactionUseFormat extends context_reaction {

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
    $formats = filter_formats();
    $format_options = array();
    foreach ($formats as $format) {
      $format_options[$format->format] = $format->name;
    }
    $form = array(
      '#title' => t('Text formats'),
      'islandora_simple_xml_format' => array(
        '#title' => t('Text formats'),
        '#description' => t('Choose a tex format to use when reaction is active.'),
        '#type' => 'select',
        '#options' => $format_options,
        '#default_value' => isset($settings['islandora_simple_xml_format']) ? $settings['islandora_simple_xml_format'] : '',
      ),
    );
    return $form;
  }
  // @codingStandardsIgnoreEnd

  /**
   * Pass the rendered viewer output to the theme preprocess function.
   */
  public function execute() {
    foreach ($this->get_contexts() as $context) {
      if ($context->reactions['islandora_simple_xml_context_reaction_use_format']['islandora_simple_xml_format']) {
        return $context->reactions['islandora_simple_xml_context_reaction_use_format']['islandora_simple_xml_format'];
      }
    }
  }

}
