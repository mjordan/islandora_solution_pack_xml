<?php

/**
 * @file
 * Implementation of Drush hooks.
 */

module_load_include('inc', 'islandora_simple_xml_batch', 'includes/preprocessor');
module_load_include('inc', 'islandora_simple_xml_batch', 'includes/object');

/**
 * Implements hook_drush_command().
 */
function islandora_simple_xml_batch_drush_command() {
  $items = array();

  $items['islandora_simple_xml_batch_preprocess'] = array(
    'aliases' => array('isxbp'),
    'description' => 'Preprocess Islandora Simple XML objects into batch queue entries.',
    'drupal dependencies' => array('islandora_batch', 'islandora_solution_pack_xml'),
    'options' => array(
      'target' => array(
        'description' => 'The target directory to scan.',
        'required' => TRUE,
      ),
      'namespace' => array(
        'description' => 'The namespace for objects created by this command.',
        'required' => TRUE,
      ),
      'parent' => array(
        'description' => 'The collection to which the generated items should be added.',
        'required' => TRUE,
      ),
      'parent_relationship_uri' => array(
        'description' => 'The namespace URI of the relationship to the parent. Defaults to "info:fedora/fedora-system:def/relations-external#".',
        'value' => 'optional',
      ),
      'parent_relationship_pred' => array(
        'description' => 'The predicate of the relationship to the parent. Defaults to "isMemberOf".',
        'value' => 'optional',
      ),
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_LOGIN,
  );

  return $items;
}

/**
 * Implements hook_drush_command().
 */
function drush_islandora_simple_xml_batch_preprocess() {
  // Due to how Drush bootstrapping works, the connection may be created
  // without credentials (when your site's front page is
  // 'islandora/object/some:object', for example). Resetting to ensure a new
  // connection gets created should fix it.
  drupal_static_reset('islandora_get_tuque_connection');
  $connection = islandora_get_tuque_connection();
  $parameters = array(
    'namespace' => drush_get_option('namespace'),
    'target' => drush_get_option('target'),
    'parent' => drush_get_option('parent'),
    'parent_relationship_uri' => drush_get_option('parent_relationship_uri', 'info:fedora/fedora-system:def/relations-external#'),
    'parent_relationship_pred' => drush_get_option('parent_relationship_pred', 'isMemberOf'),
  );

  // Run the preprocessor.
  $preprocessor = new IslandoraSimpleXmlBatchPreprocessor($connection, $parameters);
  $preprocessed = islandora_batch_handle_preprocessor($preprocessor);
  drush_log(t("SetId: @s", array('@s' => $preprocessor->getSetId())), "ok");
}

/**
 * Parent collection validation.
 */
function drush_islandora_simple_xml_batch_preprocess_validate() {
  $parent = drush_get_option('parent');
  $object = islandora_object_load($parent);
  if (!$object) {
    return drush_set_error('This is not a valid parent', dt('The specified parent (@parent) was unable to be loaded.',
      array('@parent' => $parent)));
  }
}
