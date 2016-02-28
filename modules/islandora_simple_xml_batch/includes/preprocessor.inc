<?php

/**
 * @file
 * Implementation of classes from the batch ingest framework.
 */

/**
 * Batch preprocessor class.
 */
class IslandoraSimpleXmlBatchPreprocessor extends IslandoraBatchPreprocessor {
  /**
   * Function to get the OBJ XML files from the input directory.
   */
  public function preprocess() {

    $input_path = $this->parameters['target'] . DIRECTORY_SEPARATOR . '*.xml';

    // Accumulate a list of the objects added to the queue.
    $added = array();

    // Get input files and process each one.
    foreach (glob($input_path) as $filepath) {
      // File ending in .MODS.xml are reserved for the content of
      // the MODS datastream.
      if (!preg_match('/MODS\.xml$/', $filepath)) {
        $batch_object = new IslandoraSimpleXmlBatchObject($this->connection, $filepath, $this->parameters);

        // Add the instances to the Islandora batch queue.
        $this->addToDatabase($batch_object);
        $added[] = $batch_object;
      }
    }

    return $added;
  }

}
