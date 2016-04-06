# Islandora Simple XML Context

Integrates the Islandora Simple XML Solution Pack with the Context module.

## Requirements

* [Islandora](https://github.com/Islandora/islandora)
* [Islandora XML Solution Pack](https://github.com/mjordan/islandora_solution_pack_xml)
* [Context](https://drupal.org/project/context)

## Introduction

This module provides the following Context condition:

* Root element of an OBJ XML datastream: Define a set of root element names; if the current object's OBJ datastream has a root element in this list, the condition is triggered.

There are currently no Context reactions, but some that are planned include:

* Display/hide the object's "Details" metadata
* Use a specific Islandora Simple XML viewer
* Use a specific XSLT stylesheet and/or CSS file

## Usage

Install and configure. To create a context, go to Structure > Context and click on Add. The 'Islandora Simple XML root element' condition will be available in the context form.

No additional software or libraries need to be installed.

## Maintainer

* [Mark Jordan](https://github.com/mjordan)

## Development and feedback

Pull requests are welcome, as are use cases and suggestions.

## License

* [GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)
