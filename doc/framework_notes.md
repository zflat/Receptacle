# Framework notes and resources #

The primary library used for *Receptact* is QT5 because of the following capabilities it provides:

 - Dynamic plugins
 - Rich GUI
 - TCP
 - Slot & Signal
   - Event-based programs
   - Thread communications
 - Threading
 - Unit testing
 - Logging
 - Build tools

The main benifit of using QT is that all these capabilities are supported witout adding additional dependencies. 
 
## Dynamic plugins ##

Plugins may be added to a QT application as static at compile time or dynamically. The nature of *Receptact* requires that plugins can be created and then added dynamically. The sample documentation shows the capabilities and basic approach to plugins, but there are some major pitfalls that are not well documented. 

Sampes:

 - http://www.trinitydesktop.org/docs/qt4/tools-echoplugin.html

The most notable drawback is the lack of slot/signal support for a plugin interface. The general workaround is to use a Factory pattern.

Discussion on slots & signals with plugins:

 - http://qt-project.org/forums/viewthread/1509/#7057
 - http://kunalmaemo.blogspot.com/2010/11/qt-plugin-and-signals.html
 - http://www.qtcentre.org/threads/21522-Problem-with-plugin-signals-slots
 - http://qt-project.org/forums/viewthread/12901/P15/#69527
 - http://www.qtcentre.org/threads/33441-Plugin-and-shared-class-between-plugin-and-application
 - http://dtk.inria.fr/blog/?p=502
 
Generic info on plugin architechture: http://blog.nuclex-games.com/tutorials/cxx/plugin-architecture/

## Rich GUI ##

QT is known for its GUI. Example code helps speed development.

 - http://qt-project.org/doc/qt-4.8/all-examples.html
 - http://qt-project.org/doc/qt-4.8/tutorials.html
 - http://qt-project.org/doc/qt-4.8/dialogs-extension-finddialog-cpp.html
 - http://qt-project.org/doc/qt-4.8/examples-desktop.html
 - http://qt-project.org/doc/qt-4.8/examples-designer.html
 - http://www.trinitydesktop.org/docs/qt4/layouts-flowlayout.html
 

## TCP ##

Another cornerstone of *Receptact* is modular interprocess communication. TCP offers a standard way to send messages. *Receptact* only requires basic message sending and the support for TCP in QT is more than enough.

## Slot & Signal ##

The slot and signal method allows QT applications to run asynchonously. This allows background workers to perform tasks and for the GUI to remain responsive while being able to respond to events. The slots & signals mechanism also allows for a thread-safe way for threads to communicate basic events and messages. 

## Threading ##

The threading and slots & signals go together to form another cornerstone of the *Receptact* architecture. Each plugin implements a run routine that is executed in its own thread. The setup and cleanup is managed and enabled throught the slots and signals mechanism. 

The C++ QT libraries provides better threading support than libraries from interpreted languages like Python and Ruby.

## Unit Testing ##

The QT library has standard support for unit testing. Integration testing of the GUI is possible, but not straitforward. Also, the testing tools are a bit basic. Testing seems to be designed around CI and preventing regression rather than as debugging and continuous feedback for the developer. 

Testing seems to be a weak point for QT, but there is passable support. 

## Logging ##

Logging is another fundamental component of *Receptact* since many utilities will be automation utilities. When a long-running script encounters problems, a detailed log is extremely useful. Providing a record of actions provided by utilities is a major component of *Receptact*.

## Build Tools ##

The qmake utility for generating makefiles speeds up development and allows for the repository to contain projects for unit testing, integration testing and example plugins in addition to the main project. The qmake utility may not be preferred for all projects, but *Receptact* is a small project and does not need much sophistication.

