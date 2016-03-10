# Islandora XML Solution Pack

An Islandora Solution Pack that allows for ingesting and viewing content within arbitrarily structured XML files. This solution pack offers a simpler solution to the goals of the overly complex [Islandora Feeds](https://github.com/mjordan/islandora_feeds) module, the original motivation of which can be found in [this Islandora Google group discussion](https://groups.google.com/forum/#!searchin/islandora/jordan$20database/islandora/vqJZH7bxBDc/SzSygjj1RQsJ).

## Introduction

This solution pack provides well-understood tools for ingesting and viewing XML OBJ files in Islandora. It is simpler than Islandora Feeds because:

* It does not offer any way of editing the XML files. If users need to modify an XML file, they must replace the object's OBJ datastream using the standard tools provided within an object's Datastreams tab, just like with any other solution pack's OBJ datastream.
* It does not generate any derivatives. However, the 'modules' subdirectory contains an example module that illustrates how you would generate derivatives.

Users may upload a thumbnail image and default XSLT stylesheet for each XML object. Objects managed by this solution pack also have a MODS datastream just like other Islandora objects do.

## Requirements

* [Islandora](https://github.com/Islandora/islandora)

## Configuration

The admin settings for this solution pack, available at `admin/islandora/solution_pack_config/xml`, let site administrators determine:

2. the location of a default thumbnail image for use if no object-specific thumbnail exists (this default thumbnail can also be applied in batch ingests)
4. the default Islandora viewer for objects managed by this solution pack.

Standard Drupal permissions are available for allowing users to upload object-specific thumbnails and object-specific XSLT sytlesheets.

## Rendering the OBJ datastream using XSL Transformations

The module allows the use of XSLT stylesheets to render the XML to users in the following ways:

1. Users may upload a stylesheet when they create an object managed by this solution pack. The stylesheet becomes a datastream on the object with the datastream ID 'RENDER_STYLESHEET' and is applied to the XML OBJ file when users view the object.
2. Owners of collections may upload an XSL stylesheet as a datastream on a collection object. If this datastream has an ID of 'RENDER_STYLESHEET', it is used for all XML objects that are members of the collection (unless a member object has its own RENDER_STYLESHEET datastream).
3. If neither of the above is true, the XML file is simply escaped and rendered betweem HTML &lt;pre&gt; tags, or, if a viewer module (like the one included with this solution pack) is enabled and configured, it renders the XML output.

## Rendering the OBJ datastream using viewers

This solution pack supports Islandora viewer modules, and comes with a simple viewer module that if enabled and configured as the default viewer for XML objects allows easy styling of XML files using the [Google Javascript Code Prettifier](https://github.com/google/code-prettify).

Note that if this viewer is enabled, the XML OBJ datastream content is not styled with the RENDER_STYLESHEET XSLTs as described above. However, third-party viewers are free to use the RENDER_STYLESHEET or any other stylesheet they wish.

## Batch loading

Objects managed by this module cannot be loaded using the [Islandora Batch](https://github.com/Islandora/islandora_batch), but a custom Drush-based loader is available in the `modules` subdirectory. Its README provides details on preparing content and ingesting it.

## Metadata and description display

If an XML object has a MODS datastream, its content and the "Description" content will appear at the bottom of the object display (including custom metadata display configurations), just as in other Islandora solution packs. If an object has no MODS datastream, no metadata or description will appear.

## Indexing XML content

By default, all content is slurped into one field for simple search as it is with any other XML datastream, but it is possible to configure FedoraGSearch to index specific fields so they can be used in advanced search forms and in Solr-based metadata displays. To have FedoraGSearch do this:

1. Create an XSLT stylesheet to create the Solr fields. An annotate example is provided in this module's `extras/indexing_stylesheets` directory. Place your transform in your `tomcat/webapps/fedoragsearch/WEB-INF/classes/fgsconfigFinal/index/FgsIndex/islandora_transforms` directory (or wherever your FedoraGSearch configs are located) with the other stylesheets.
2. Include the stylesheet from within your foxmlToSolr.xslt stylesheet, following the pattern of other stylesheets in the `islandora_transforms` directory.
3. On reindexing, or on ingest of new simple XML objects, each of the fields created in your stylesheet will be added to the object's Solr document. You will not need to modify your Solr schema or configuration for this to work.

## To do

* Add checks for well formedness on XML and XSLT files as they are uploaded.
* Add checks for validity against a specific schema or DTD
  * Possible solution is to attach a schema file to the collection object as a datastream.
* Write some additional viewers that present the XML content in interesting ways
  * Like [this](https://www.sencha.com/forum/showthread.php?163680-Implementing-treeview-using-xml-data) or [this](http://blog.ashwani.co.in/blog/2013-07-18/stylize-your-xml-with-jquery-xml-tree-plugin/).
* Provide sample render XSLT stylesheets for common types of XML objects, like TEI, EAD, etc.

## Maintainer

* [Mark Jordan](https://github.com/mjordan)

## Development and feedback

Pull requests are welcome, as are use cases and suggestions.

## License

* [GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)
