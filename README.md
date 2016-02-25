# Islandora XML Solution Pack

Islandora Solution Pack that allows for ingesting and viewing XML files.

## Introduction and usage

This module provides basic support for ingesting and viewing XML OBJ files in Islandora.

The solution pack is "simple" because:

1. It does not offer any way of editing the XML files. If users need to modify an XML file, they must "replace" the object's OBJ datastream.
2. It does not generate any derivatives.

The module allows the use of XSL stylesheets in the following ways:

1. Users may upload a stylesheet when they create an object managed by this solution pack. The stylesheet becomes a datastream on the object with the datastream ID 'RENDER_STYLESHEET' and is applied to the XML OBJ file when users view the object.
2. Owners of collections may upload an XSL stylesheet as a datastream on a collecion object. If this datastream has a datastream ID of 'RENDER_STYLESHEET,' it is used for all XML objects that are memebers of the collection (unless an object has its own RENDER_STYLESHEET datastream).

Users may also upload a thumbnail image for their XML object.

## Viewers

This module comes with an Islandora viewer that if enabled and configured as the default viewer for XML objects allows easy styling of XML files using the [Google Javascript Prettifier](https://github.com/google/code-prettify). Note that if this viewer is enabled, the XML content is not styled with the RENDER_STYLESHEET XSLTs as described above.

## Requirements

* [Islandora](https://github.com/Islandora/islandora)

## Maintainer

* [Mark Jordan](https://github.com/mjordan)

## To do

* Add checks for well formedness on XML and XSLT files as they are uploaded.
* Figure out strategies for batch loading objects managed by this solution pack (maybe create a [custom batch module](https://github.com/Islandora/islandora_batch/wiki/Example-Implementation-Tutorial)).
* Write some additional viewers that present the XML content in interesting ways.
* Provide Solr configs for allowing the indexing of XML element content for advanced searches.

## Development and feedback

Pull requests are welcome, as are use cases and suggestions.

## License

* [GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)
