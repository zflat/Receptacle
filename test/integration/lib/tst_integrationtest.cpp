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

#include "test_launcher.h"
#include "test_print.h"
#include "test_utils_populated.h"

int main(int argc, char *argv[]){

    // Construct application before running tests
    // http://stackoverflow.com/a/16711202
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);

    TestUtilsPopulated test1;
    QTest::qExec(&test1, argc, argv);

    TestLauncher* test2=new TestLauncher();
    QTest::qExec(test2, argc, argv);
    delete test2;

    TestPrint* test3=new TestPrint();
    QTest::qExec(test3, argc, argv);
    delete test3;

    qApp->exit(0);
    return 0;
}


#include "tst_integrationtest.moc"


// testrunner approach
// see http://stackoverflow.com/questions/1524390/what-unit-testing-framework-should-i-use-for-qt
