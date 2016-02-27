<?php

/**
 * @file
 * Handles the uploading of the XML object file as part of the ingest process.
 */

/**
 * Defines a file upload form for uploading the XML file.
 *
 * @param array $form
 *   The drupal form.
 * @param array $form_state
 *   The drupal form state.
 *
 * @return array
 *   The drupal form definition.
 */
function islandora_solution_pack_xml_xml_upload_form(array $form, array &$form_state) {
  $upload_size = min((int) ini_get('post_max_size'), (int) ini_get('upload_max_filesize'));
  $extensions = array('xml');
  $form = array();
  $form['file'] = array(
    '#title' => t('XML object file'),
    '#type' => 'managed_file',
    '#required' => TRUE,
    '#description' => t('Select file to upload.<br/>Files must be less than <strong>@size MB.</strong><br/>Allowed file types: <strong>@ext.</strong>', array('@size' => $upload_size, '@ext' => $extensions[0])),
    '#default_value' => isset($form_state['values']['files']) ? $form_state['values']['files'] : NULL,
    '#upload_location' => 'temporary://',
    '#upload_validators' => array(
      'file_validate_extensions' => $extensions,
      // Assume it's specified in MB.
      'file_validate_size' => array($upload_size * 1024 * 1024),
    ),
  );

  if (variable_get('islandora_solution_pack_xml_allow_thumbnail_upload', TRUE)) {
    $form['islandora_solution_pack_xml_thumbnail_upload'] = array(
      '#type' => 'checkbox',
      '#title' => t("Add a custom thumbnail to this object?"),
      '#default_value' => FALSE,
    );
    $form['thumbnail'] = array(
      '#title' => t('Thumbnail image'),
      '#type' => 'managed_file',
      '#required' => FALSE,
      '#description' => t('Select thumbnail file to upload.<br/>Files must be less than <strong>@size MB.</strong><br/>Allowed file types: <strong>@ext.</strong><br />This file is optional.', array('@size' => $upload_size, '@ext' => 'jpg, png, gif')),
      '#default_value' => isset($form_state['values']['files']) ? $form_state['values']['files'] : NULL,
      '#upload_location' => 'temporary://',
      '#upload_validators' => array(
        'file_validate_extensions' => array('jpg', 'png', 'gif'),
        // Assume it's specified in MB.
        'file_validate_size' => array($upload_size * 1024 * 1024),
      ),
      '#states' => array(
        'visible' => array(
          ':input[name="islandora_solution_pack_xml_thumbnail_upload"]' => array('checked' => TRUE),
        ),
      ),
    );
  }

  if (variable_get('islandora_solution_pack_xml_allow_render_stylesheet_upload', TRUE)) {
    $form['islandora_solution_pack_xml_render_stylesheet_upload'] = array(
      '#type' => 'checkbox',
      '#title' => t("Add a render stylesheet file to this object?"),
      '#default_value' => FALSE,
    );
    $form['render_stylesheet'] = array(
      '#title' => t('XSLT stylesheet used for rendering this XML file'),
      '#type' => 'managed_file',
      '#required' => FALSE,
      '#description' => t('Select XSLT file to upload.<br/>Files must be less than <strong>@size MB.</strong><br/>Allowed file types: <strong>@ext.</strong><br />This file is optional.', array('@size' => $upload_size, '@ext' => 'txt')),
      '#default_value' => isset($form_state['values']['files']) ? $form_state['values']['files'] : NULL,
      '#upload_location' => 'temporary://',
      '#upload_validators' => array(
        'file_validate_extensions' => array('xsl', 'xslt'),
        // Assume it's specified in MB.
        'file_validate_size' => array($upload_size * 1024 * 1024),
      ),
      '#states' => array(
        'visible' => array(
          ':input[name="islandora_solution_pack_xml_render_stylesheet_upload"]' => array('checked' => TRUE),
        ),
      ),
    );
  }
  return $form;
}

/**
 * Addes the uploaded file into the ingestable objects 'OBJ' datastream.
 *
 * @param array $form
 *   The drupal form.
 * @param array $form_state
 *   The drupal form state.
 */
function islandora_solution_pack_xml_xml_upload_form_submit(array $form, array &$form_state) {
  $object = islandora_ingest_form_get_object($form_state);
  if (empty($object['OBJ'])) {
    $ds = $object->constructDatastream('OBJ', 'M');
    $object->ingestDatastream($ds);
  }
  else {
    $ds = $object['OBJ'];
  }
  $xml_file = file_load($form_state['values']['file']);
  $xml_path = drupal_realpath($xml_file->uri);
  $ds->setContentFromFile($xml_path, FALSE);
  $ds->label = $xml_file->filename;
  $ds->mimetype = $xml_file->filemime;

  if (isset($form_state['values']['thumbnail']) && ($form_state['values']['thumbnail'] > 0)) {
    if (empty($object['TN'])) {
      $ds = $object->constructDatastream('TN', 'M');
      $object->ingestDatastream($ds);
    }
    else {
      $ds = $object['TN'];
    }
    $thumbnail_file = file_load($form_state['values']['thumbnail']);
    $thumbnail_path = drupal_realpath($thumbnail_file->uri);
    $ds->setContentFromFile($thumbnail_path, FALSE);
    $ds->label = $thumbnail_file->filename;
    $ds->mimetype = $thumbnail_file->filemime;
  }
  else {
    // Use default thumbnail.
    $default_thumbnail_path = variable_get('islandora_solution_pack_xml_default_thumbnail_path', '');
    if (strlen($default_thumbnail_path)) {
      if (empty($object['TN'])) {
        $ds = $object->constructDatastream('TN', 'M');
        $object->ingestDatastream($ds);
      }
      else {
        $ds = $object['TN'];
      }
      $thumbnail_path = DRUPAL_ROOT . DIRECTORY_SEPARATOR . $default_thumbnail_path;
      $thumbnail_mime_detector = new MimeDetect();
      $ds->mimetype = $thumbnail_mime_detector->getMimetype($thumbnail_path);
      $ds->label = 'Thumbnail';
      $ds->setContentFromFile($thumbnail_path, FALSE);
    }
  }

  if (isset($form_state['values']['render_stylesheet']) && ($form_state['values']['render_stylesheet'] > 0)) {
    if (empty($object['RENDER_STYLESHEET'])) {
      $ds = $object->constructDatastream('RENDER_STYLESHEET', 'M');
      $object->ingestDatastream($ds);
    }
    else {
      $ds = $object['RENDER_STYLESHEET'];
    }
    $render_stylesheet_file = file_load($form_state['values']['render_stylesheet']);
    $render_stylesheet_path = drupal_realpath($render_stylesheet_file->uri);
    $ds->setContentFromFile($render_stylesheet_path, FALSE);
    $ds->label = $render_stylesheet_file->filename;
    $ds->mimetype = $render_stylesheet_file->filemime;
  }
}
