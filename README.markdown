
Receptacle {#mainpage}
=========

Desktop application for running automation utilities.

## What is Receptacle?

Receptacle is a desktop application that serves as a host for plugins. The hosted plugins typically perform desktop automation jobs and may use a GUI.

## About plugins

Plugins have two main parts that follow a factory pattern. The first part implements UtilInterface and provides information describing the plugin and is used to construct a background worker. The second part of a plugin implements UtilWorkerInterface and is the background worker that contains the subroutine logic the plugin executes.  

### Developing a plugin

Create a library application that follows the [QT plugin API][1] and implement UtilInterface and UtilWorkerInterface. See the examples under /test/example_plugins for more information. 

### Adding a plugin to the application
Plugins are discovered at runtime. Plugins are made available to the application by placing the plugin library into a /plugins subdirectory from the executable. 

# Documentation

## Architecture Diagrams

See /doc for diagrams showing the general architecture of Receptacle.

## Doxygen

Classes and methods are documented in the code and then HTML documentation is generated using doxygen.

See https://chronodekar.wordpress.com/2013/12/19/configuring-doxygen-with-github/ for the setup to send doxygen as github pages.

## Specifying version

See http://www.openguru.com/2009/11/qt-best-way-to-set-application-version.html
and http://qt-project.org/faq/answer/how_can_i_add_version_information_to_my_application

    qDebug() << QT_VERSION_STR;

# Copyright

(c) 2014 William Wedler, See COPYING and COPYING.LESSER for details. The [FLOSS licence guide][2] provides a compatibility summary.


  [1]: http://qt-project.org/doc/qt-4.8/plugins-howto.html
  [2]: http://www.dwheeler.com/essays/floss-license-slide.html