# Platform specific notes #

## Windows ##

### Dev Setup Notes ###

Install Windows SDK 7.1

Uninstall any Visual C++ 2010 runtime newer than 10.0.30319
http://ctrlf5.net/?p=184

Download and run 64 bit installer & creator
http://www.tver-soft.org/qt64

Install compiler update to fix "LNK1123: failure"
http://www.microsoft.com/en-au/download/details.aspx?id=4422
https://qt-project.org/wiki/Category:Tools::msvc



Other ways to install
http://qtitkvtkhelp.blogspot.in/2012/11/qt-installation-prerequisite-1.html
http://blogs.msdn.com/b/gpalem/archive/2009/03/09/how-to-make-qt-sdk-work-with-visualstudio-2008-express-complete.aspx


### Deployment Notes ###

http://qt-project.org/doc/qt-5/windows-deployment.html

How to hide console:
http://qt-project.org/forums/viewthread/20168

#### Configuration ####

See /build/config.json.sample for the basic structure for configuring the application. Place a file name config.json in the application directory to provide default configuration.