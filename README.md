# Islandora XML Solution Pack [![Build Status](https://travis-ci.org/mjordan/islandora_solution_pack_xml.png?branch=7.x)](https://travis-ci.org/mjordan/islandora_solution_pack_xml)

An Islandora Solution Pack that allows for ingesting and viewing arbitrary types of XML files. This solution pack is not intended to replace others that offer more comprehensive and specialized tools for XML formats like [EAD](https://github.com/DrexelUniversityLibraries/islandora_solution_pack_ead) and [TEI](https://github.com/discoverygarden/islandora_solution_pack_manuscript). Instead, its focus is on being a general-purpose solution for making a variety of types of XML content accessible. It offers a simpler solution to the goals of the overly complex [Islandora Feeds](https://github.com/mjordan/islandora_feeds) module, the original motivation for which can be found in [this Islandora Google group discussion](https://groups.google.com/forum/#!searchin/islandora/jordan$20database/islandora/vqJZH7bxBDc/SzSygjj1RQsJ).

## Introduction

This solution pack provides well-understood tools for ingesting and viewing XML OBJ files in Islandora. These files could be TEI, EAD, DocBook, SVG, or locally defined XML. It is simpler than Islandora Feeds because:

* It offers only a very rudimentary way of editing an XML file - just a plain text area. Users who need to modify an XML file using more sophisticated tools must download the object's OBJ XML datastream, edit it outside of Islandora, and upload it using the "Replace" link provided within the object's Datastreams tab. The editing feature in this module is intended for fixing typos, etc. and performs no well-formedness checking or validation on the edited XML content.
* It does not generate any derivatives. However, the 'modules' subdirectory contains an example module that illustrates how you would generate derivatives.

Users may upload a thumbnail image and default XSLT stylesheet for each XML object. Objects managed by this solution pack can also have a MODS datastream just like other Islandora objects do.

## Requirements

* [Islandora](https://github.com/Islandora/islandora)

## Configuration

The admin settings for this solution pack, available at `admin/islandora/solution_pack_config/xml`, let site administrators determine:

1. the location of a default thumbnail image for use if no object-specific thumbnail exists (this default thumbnail can also be applied in batch ingests)
2. the ID of the datastream that needs to be present to render metadata and description at the bottom of the object display.
3. the Islandora viewer for objects managed by this solution pack

Standard Drupal permissions are available for allowing users to upload object-specific thumbnails and object-specific XSLT sytlesheets.

## Rendering the OBJ datastream using XSL Transformations

The module allows the use of XSLT stylesheets to render the XML to users in the following ways:

1. Users may upload a stylesheet when they create an object managed by this solution pack. The stylesheet becomes a datastream on the object with the datastream ID 'RENDER_STYLESHEET' and is applied to the XML OBJ file when users view the object.
2. Owners of collections may upload an XSL stylesheet as a datastream on a collection object. If this datastream has an ID of 'RENDER_STYLESHEET', it is used for all XML objects that are members of the collection (unless a member object has its own RENDER_STYLESHEET datastream).
3. If neither of the above is true, the XML file is simply escaped and rendered betweem HTML &lt;pre&gt; tags, or, if a viewer module (like the one included with this solution pack) is enabled and configured, it renders the XML output.

In cases 1 and 2, parameters can be passed to the XSLT stylesheet via URL query parameters, e.g. `http://host/islandora/object/islandora:29?foo=true&bar=Mark`. The values of `foo` and `bar` would then be accessible in the render stylesheet as follows:

```xml
  <xsl:param name="foo"></xsl:param>
  <xsl:param name="bar"></xsl:param>

  <xsl:if test="$foo='true' and $bar">
    <div>Hello <span><xsl:value-of select="$bar"/></span></div>
  </xsl:if>
```

The parameter 'pid' is always passed to the stylesheet, and is accessible as follows:

```xml
  <xsl:param name="pid"></xsl:param>
```

More detail on using parameters in RENDER_STYLESHEETs is [available](https://github.com/mjordan/islandora_solution_pack_xml/tree/7.x/extras/parameters_tutorial).

## Rendering the OBJ datastream using viewers

This solution pack supports Islandora viewer modules, and comes with a simple viewer module that if enabled and configured as the default viewer for XML objects allows easy styling of XML files using the [Google Javascript Code Prettifier](https://github.com/google/code-prettify). Viewers may also be defined by the Islandora Simple XML Context module, which is included with this one. Michael Joyce has written a viewer for [a specific set of TEI documents](https://github.com/ubermichael/ballads_viewer).

Note that if a viewer is enabled, the XML OBJ datastream content is not styled with the RENDER_STYLESHEET XSLTs as described above. However, third-party viewers are free to use the RENDER_STYLESHEET or any other stylesheet they wish.

## Metadata and description display

If an XML object has a MODS datastream, its content and the "Description" content will appear at the bottom of the object display (including custom metadata display configurations), just as in other Islandora solution packs. If an object has no MODS datastream, no metadata or description will appear. A datastream ID other than 'MODS' can be configured in the module's admin settings.

## Batch loading

Objects managed by this module cannot be loaded using the [Islandora Batch](https://github.com/Islandora/islandora_batch), but a custom Drush-based loader is available in the `modules` subdirectory. Its README provides details on preparing content and ingesting it.

## Using Contexts

The [Islandora Simple XML Context](https://github.com/mjordan/islandora_solution_pack_xml/tree/7.x/modules/islandora_simple_xml_context), included in the `modules` subdirectory, provides integration with the [Context](https://www.drupal.org/project/context) contrib module. More information is provided in its README file.


## Indexing XML content

By default, all content is slurped into one field for simple search as it is with any other XML datastream, but it is possible to configure FedoraGSearch to index specific fields so they can be used in advanced search forms and in Solr-based metadata displays. To have FedoraGSearch do this:

1. Create an XSLT stylesheet to create the Solr fields. An annotate example is provided in this module's `extras/sample_stylesheets` directory. Place your transform in your `tomcat/webapps/fedoragsearch/WEB-INF/classes/fgsconfigFinal/index/FgsIndex/islandora_transforms` directory (or wherever your FedoraGSearch configs are located) with the other stylesheets.
2. Include the stylesheet from within your `foxmlToSolr.xslt` stylesheet, following the pattern of other stylesheets in the `islandora_transforms` directory.
3. On reindexing, or on ingest of new simple XML objects, each of the fields created in your stylesheet will be added to the object's Solr document. You will not need to modify your Solr schema or configuration for this to work.

## To do

Some features that would be useful include:

* sample render XSLT stylesheets for common types of XML objects, like TEI, EAD, DocBook (partially addressed [here](https://github.com/mjordan/islandora_solution_pack_xml/blob/7.x/extras/parameters_tutorial/RENDER_STYLESHEET.xsl)), etc.
* checks for well formedness on XML and XSLT files as they are uploaded
* checks for validity against a specific schema or DTD
  * Possible solution is to attach a schema file to the collection object as a datastream
* additional viewers that present the XML content in interesting ways
  * for example as [browsable trees](http://blog.ashwani.co.in/blog/2013-07-18/stylize-your-xml-with-jquery-xml-tree-plugin/) or [SVG graphics](https://github.com/ariutta/svg-pan-zoom)
* caching of the rendered versions of large or expensive-to-render XML files (which may be done best in viewers).

## Maintainer

* [Mark Jordan](https://github.com/mjordan)

## Development and feedback

Pull requests are welcome, as are use cases and suggestions.

## License

* [GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)
