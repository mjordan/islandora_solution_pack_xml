# Islandora Simple XML HTML Viewer

Islandora viewer that renders HTML datastreams managed by the Islandora XML Solution Pack.

Note that "HTML" here refers to markup within a standard HTML file's `<body>` tag. 

## Requirements

* [Islandora](https://github.com/Islandora/islandora)
* [Islandora XML Solution Pack](https://github.com/mjordan/islandora_solution_pack_xml)

## Usage

Enable this module, then select it as a viewer in the XML Solution Pack's admin settings. No additional software or libraries need to be installed.

The XML Solution Pack has an admin option to select which output filter to use in its viewers. If your HTML is not rendering as intended, make sure that the filter being applied is not configured correctly.

## Maintainer

* [Mark Jordan](https://github.com/mjordan)

## Development and feedback

Pull requests are welcome, as are use cases and suggestions.

## License

* [GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)
