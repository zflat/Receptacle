
# Receptacle

Desktop application for running automation utilities.

## What is Receptacle?

Receptacle is a desktop application that serves as a host for plugins. The hosted plugins typically perform desktop automation jobs and may use a GUI.

## About plugins

Plugins have two main parts that follow a factory pattern. The first part implements UtilInterface and provides information describing the plugin and is used to construct a background worker. The second part of a plugin implements UtilWorkerInterface and is the background worker that contains the subroutine logic the plugin executes.  

### Developing a plugin

Create a library application that follows the [QT plugin API][1] and implement UtilInterface and UtilWorkerInterface. See the examples under /test/example_plugins for more information. 

### Adding a plugin to the application
Plugins are discovered at runtime. Plugins are made available to the application by placing the plugin library into a /plugins subdirectory from the executable. 

# Copyright

(c) 2014 William Wedler, See COPYING and COPYING.LESSER for details. The [FLOSS licence guide][2] provides a compatibility summary.


  [1]: http://qt-project.org/doc/qt-4.8/plugins-howto.html
  [2]: http://www.dwheeler.com/essays/floss-license-slide.html