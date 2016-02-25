# Islandora Simple XML Batch

Islandora batch module for loading XML files managed by the Islandora XML Solution Pack. We can't use Islandora Batch because it treats .xml files as MODS or DC datastreams.

## Requirements

* [Islandora](https://github.com/Islandora/islandora)
* [Islandora Batch](https://github.com/Islandora/islandora_batch)

## Usage

Enable this module, then run its drush command to import objects:

`drush --user=admin islandora_simple_xml_batch_preprocess --target=/path/to/XML/files --namespace=foo --parent=islandora:mycollection`

Then, to perform the ingest:

`drush --user=admin islandora_batch_ingest`

## Maintainer

* [Mark Jordan](https://github.com/mjordan)

## Development and feedback

Pull requests are welcome, as are use cases and suggestions.

## License

* [GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)
