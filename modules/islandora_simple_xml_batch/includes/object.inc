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

  // Responsible for pre-ingest transformations into base datastreams.
  public function batchProcess() {

/*
    // Grab things from the XML into variables, as strings.
    $this->label = $title = (string) $simple_xml->title;
    $description = (string) $simple_xml->description;
    $url = (string) $simple_xml->link;
*/

    $obj = $this->constructDatastream('OBJ', 'M');
    $obj->label = "Hi";
    $obj->mimetype = 'text/xml';
    $obj->setContentFromFile($this->xml_obj_file_path, FALSE);
    $this->ingestDatastream($obj);

    // Generate a simple MODS datastream, and add it to the current object.
    // Typically, the MODS would also be transformed to DC and added, but
    // we're skipping this, due to the simple data.

    // @todo: Add a 'label' parameter to batch which identifies the element that is to be
    // used as the object label. If absent, assign a default label or get one from the MODS
    // file if it is present. Maybe also add a parameter for description?

    // @todo: If a file named xxx.mods is present, use it instead of generating one.
    $mods = $this->constructDatastream('MODS', 'M');
    // $mods->label = $title;
    $mods->label = 'New XML object MODS';
    $mods->mimetype = 'text/xml';
    $mods->content = <<<EOQ
<mods xmlns='http://www.loc.gov/mods/v3'>
  <titleInfo>
    <title>Hi there</title>
  </titleInfo>
  <abstract>Duh, I am an abstract</abstract>
</mods>
EOQ;
    $this->ingestDatastream($mods);

    //@todo: Create TN datastream from a file matching the base object.

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
}
