# Islandora Simple XML Context

Integrates the Islandora Simple XML Solution Pack with the Context module.

## Requirements

* [Islandora](https://github.com/Islandora/islandora)
* [Islandora XML Solution Pack](https://github.com/mjordan/islandora_solution_pack_xml)
* [Context](https://drupal.org/project/context)

No additional software or libraries need to be installed. [Islandora Context](https://github.com/mjordan/islandora_context) is not required but offers some additional conditions and reactions that may be useful in combination with those provided by this module.

## Introduction

This module provides the following Context condition:

* Root element of an OBJ XML datastream: Define a set of root element names; if the current object's OBJ datastream has a root element in this list, the condition is triggered.

And the following Context reaction:

* Use a specific Islandora Simple XML viewer

## Usage

Install as any other module. To create a context, go to Structure > Context and click on Add. The condition and reaction listed above will appear in their respective sections of the context form.

## Maintainer

* [Mark Jordan](https://github.com/mjordan)

## Development and feedback

Pull requests are welcome, as are use cases and suggestions.

## License

* [GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)
