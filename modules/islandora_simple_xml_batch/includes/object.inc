<?php

/**
 * @file
 * Implementation of classes from the batch ingest framework.
 */

class IslandoraSimpleXmlBatchObject extends IslandoraBatchObject {
  protected $xml_obj_file_path;
  protected $preprocessorParameters;

  public function __construct(IslandoraTuque $connection, string $xml_file_path, $batch_parameters) {
    parent::__construct(NULL, $connection->repository);

    $this->xml_obj_file_path = $xml_file_path;
    $this->preprocessorParameters = $batch_parameters;
  }

  // Generate datastreams.
  public function batchProcess() {
    // OBJ datastream.
    $obj = $this->constructDatastream('OBJ', 'M');
    $obj->label = 'OBJ Datastream';
    $obj->mimetype = 'text/xml';
    $obj->setContentFromFile($this->xml_obj_file_path, FALSE);
    $this->ingestDatastream($obj);

    // MODS, then DC datastreams.
    if ($mods = $this->getMods()) {
      $this->ingestDatastream($mods);

      module_load_include('inc', 'islandora_solution_pack_xml', 'includes/utilities');
      $path_to_mods_to_dc_xsl = drupal_get_path('module', 'islandora_batch') . '/transforms/mods_to_dc.xsl';
      $mods_to_dc_xsl = file_get_contents($path_to_mods_to_dc_xsl);
      $dc_content = islandora_solution_pack_xml_apply_xslt($mods_to_dc_xsl, $mods->content); 
      $dc = $this->constructDatastream('DC', 'M');
      $dc->mimetype = 'text/xml';
      $dc->label = 'DC Record';
      $dc->setContentFromString($dc_content);
      $this->ingestDatastream($dc);

      // Get object label from dc:title.
      $dom = new DOMDocument();
      $dom->loadXML($dc_content);
      $xpath = new DOMXPath($dom);
      $xpath->registerNamespace('dc', 'http://purl.org/dc/elements/1.1/');
      $titles = $xpath->query("//dc:title");
      if ($titles->length > 0) {
        $this->label = $titles->item(0)->nodeValue;
      }
      else {
        $this->label = '[No object label available]';
      }
    }

    // TN datastream.
    if ($tn = $this->getTn()) {
      $this->ingestDatastream($tn);
    }

    // Add relationships.
    $this->addRelationships();

    // Indicate that this object is ready to actually go into Fedora.
    return ISLANDORA_BATCH_STATE__DONE;
  }

  // Add relationships.
  public function addRelationships() {
    // Let's make this object a citation in the default citation collection, as
    // MODS is all that is really required to make a citation...
    $this->relationships->add(FEDORA_RELS_EXT_URI, 'isMemberOfCollection', $this->preprocessorParameters['parent']);
    $this->models = 'islandora:sp_simple_xml';
  }

  // Get a list of resources.
  public function getResources() {
    return array();
  }

  /**
   * Creates a TN datastream from a file matching the base object.
   *
   * @return object|FALSE
   */
  private function getTn() {
    $tn_extensions = array('png', 'jpg', 'jpeg', 'gif');
    $pathinfo = pathinfo($this->xml_obj_file_path);
    $dir_name = $pathinfo['dirname'];
    $file_name = $pathinfo['filename'];
    foreach ($tn_extensions as $ext) {
      $tn_file_path = $dir_name . DIRECTORY_SEPARATOR . $file_name . '.TN.' . $ext;
      if (file_exists($tn_file_path)) {
        $tn_mime_detector = new MimeDetect();
        $tn = $this->constructDatastream('TN', 'M');
        $tn->mimetype = $tn_mime_detector->getMimetype($tn_file_path);
        $tn->label = 'Thumbnail';
        $tn->setContentFromFile($tn_file_path, FALSE);
        return $tn;
      }
    }
    return FALSE;
  } 

  /**
   * Creates a MODS datastream.
   *
   * If a file in the same directory as the OBJ file and matching its basename
   * plus '.MODS.xml' exists, populates the MODS datastream with that file;
   * if no such file exists, generates a minimal, templated MODS datastream.
   *
   * @return obj
   */
  private function getMods() {
    $pathinfo = pathinfo($this->xml_obj_file_path);
    $dir_name = $pathinfo['dirname'];
    $file_name = $pathinfo['filename'];
    $mods_file_path = $dir_name . DIRECTORY_SEPARATOR . $file_name . '.MODS.xml';
    if (file_exists($mods_file_path)) {
      $mods = $this->constructDatastream('MODS', 'M');
      $mods->mimetype = 'text/xml';
      $mods->label = 'MODS metadata';
      $mods->setContentFromFile($mods_file_path, FALSE);
      return $mods;
    }
    else {
      // @todo: Generate a minimal MODS file.
      $mods = $this->constructDatastream('MODS', 'M');
      $mods->content = <<<EOQ
<mods xmlns='http://www.loc.gov/mods/v3'>
  <titleInfo>
    <title>{$file_name}</title>
  </titleInfo>
</mods>
EOQ;
      $mods->mimetype = 'text/xml';
      $mods->label = 'MODS metadata';
      return $mods;
    }
  } 

  /**
   * Creates a RENDER_STYLESHEET datastream from a file matching the base object.
   *
   * @return object|FALSE
   */
  private function getRenderStylesheet() {
    $pathinfo = pathinfo($this->xml_obj_file_path);
    $dir_name = $pathinfo['dirname'];
    $file_name = $pathinfo['filename'];
    $rs_file_path = $dir_name . DIRECTORY_SEPARATOR . $file_name . '.xsl';
    if (file_exists($mods_file_path)) {
      $rs = $this->constructDatastream('RENDER_STYLESHEET', 'M');
      $rs->mimetype = 'text/xml';
      $rs->label = 'Render stylesheet';
      $rs->setContentFromFile($rs_file_path, FALSE);
      return $rs;
    }
    else {
      return FALSE;
    }
  } 

}
