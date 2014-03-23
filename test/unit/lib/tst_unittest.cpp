/*

Copyright 2014 William Wedler

This file is part of Receptacle

Receptacle is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Receptacle is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Receptacle.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include "test_util_collection.h"
#include "test_log_text_page.h"
#include "test_log_emitter.h"
#include <QPointer>
#include <stdio.h>


int main(int argc, char *argv[]){
    // Construct application before running tests
    // http://stackoverflow.com/a/16711202
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);

    TestUtilCollection testutilcollection;
    QTest::qExec(&testutilcollection, argc, argv);

    TestLogText testlogtext;
    QTest::qExec(&testlogtext, argc, argv);

    TestLogEmitter testlogemitter;
    QTest::qExec(&testlogemitter, argc, argv);


    if(false){app.exec();}
    return(0);
}


#include "tst_unittest.moc"


// testrunner approach
// see http://stackoverflow.com/questions/1524390/what-unit-testing-framework-should-i-use-for-qt
