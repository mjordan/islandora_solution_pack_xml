# Islandora Simple XML Batch

Islandora batch module for loading XML files managed by the Islandora XML Solution Pack. We can't use Islandora Batch because it treats .xml files as MODS or DC datastreams.

## Requirements

* [Islandora](https://github.com/Islandora/islandora)
* [Islandora Batch](https://github.com/Islandora/islandora_batch)
* Islandora Simple XML Solution Pack

## Usage

Enable this module, then run its drush command to import objects:

`drush --user=admin islandora_simple_xml_batch_preprocess --target=/path/to/XML/files --namespace=foo --parent=islandora:mycollection`

Then, to perform the ingest:

`drush --user=admin islandora_batch_ingest`

## Preparing your content files for ingesting

This batch module uses filename patterns to identify the files that are intended for specific datastreams. All of the files you are ingesting should go in the same directory (the one you identify in the drush command with the `--target` option), and you must have at least a file for the OJB datastream. All other files are optional. Using this module, you can batch ingest objects of content model 'islandora:sp_simple_xml' having the following datastreams.

### OBJ datastreams

XML files with the extension `.xml`.

It's a very good idea to check the XML files for well formedness and if applicable, validity before ingesting them.

### TN datastreams

OBJ file base name with the double extension `.TN.ext` where `.ext` is one of '.jpg', '.jpeg', '.png', or '.gif'.

### MODS datastreams

OBJ file base name with the double extension `.MODS.xml`.

### RENDER_STYLESHEET datastreams

OBJ file base name plus the extension `.xsl`.

### Example input directories

Two XML files, which will create two objects. The thumbnail and MODS datastreams for the objects will be set to defaults:

```
.
├── foo.xml
└── bar.xml
```

Two XML files, which will create two objects. The thumbnail and MODS datastreams for the objects will be created from the file with TN and MODS in their filenames:

```
.
├── foo.xml
├── foo.MODS.xml
├── foo.TN.jpg
├── bar.xml
├── bar.MODS.xml
└── bar.TN.png
```

Two XML files, which will create two objects. The object created from `foo.xml` will have its MODS datastream created from the `foo.MODS.xml` and its thumbnail created from defaults; the object created from `bar.xml` will have its TN datastream created from `bar.TN.jpg` and its MODS datastream created from defaults; the object created from `baz.xml` will have its TN and MODS datastreams created from defaults and will have its RENDER_STYLESHEET datastream created from `baz.xsl`:

```
.
├── foo.xml
├── foo.MODS.xml
├── bar.xml
├── bar.TN.png
├── baz.xml
└── baz.xsl
```

## Maintainer

* [Mark Jordan](https://github.com/mjordan)

## Development and feedback

Pull requests are welcome, as are use cases and suggestions.

## License

* [GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)
