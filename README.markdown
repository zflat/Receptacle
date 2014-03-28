
Receptacle
=========

Receptacle is a desktop application that serves as a host for plugins. The hosted plugins typically perform desktop automation jobs and may use a GUI.

[See the full documentation.][1] 

## Dependencies

 - Qt 5.2

## Build
    
    cd Receptacle/build
    qmake ../lib && make

## Test

### Unit Tests

    cd test/unit/build
    qmake ../lib && make
    ./tst_unittest

### Integration Tests

    cd test/integration/build/debug
    qmake ../../lib && make
    ./tst_integrationtest
    
## Document

    cd Receptacle
    doxygen doc/Doxyfile


# Copyright

2014 William Wedler, See COPYING and COPYING.LESSER for details. The [FLOSS licence guide][2] provides a compatibility summary.


  [1]: http://zflat.github.io/Receptacle/
