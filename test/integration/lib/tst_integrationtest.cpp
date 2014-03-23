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


#include "dispatcher.h"
#include "util_collection.h"
#include "host_controller.h"

class IntegrationTest : public QObject
{
    Q_OBJECT

public:
    IntegrationTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testOpenCloseLauncher();
private:
    Dispatcher* server;
    HostController* host;
};

IntegrationTest::IntegrationTest()
{
}

void IntegrationTest::initTestCase()
{
    /*
    int argc =0;
    char* argv = new char[0];
    QApplication app(argc, &argv);
    app.setQuitOnLastWindowClosed(false);
    */

    qApp->setQuitOnLastWindowClosed(false);
    UtilCollection* utils = new UtilCollection();
    host = new HostController(utils);

    // Create an instance of a server and then start it.
    server = new Dispatcher(host);
    server->startServer();
    return;
}

void IntegrationTest::cleanupTestCase()
{
    qDebug() << "Server cleanup";
    delete server;
    qApp->exit(0);
}

void IntegrationTest::testOpenCloseLauncher()
{
    server->queue_request("cmd");
    host->kill_job();
    QTRY_VERIFY_WITH_TIMEOUT(!server->queue_busy(), 1000);
    QVERIFY2(true, "Failure");
}

QTEST_MAIN(IntegrationTest)
/*
int main(int argc, char *argv[])
{
    IntegrationTest test1;
    QTest::qExec(&test1, argc, argv);

    return 0;
}
*/


#include "tst_integrationtest.moc"



// testrunner approach
// see http://stackoverflow.com/questions/1524390/what-unit-testing-framework-should-i-use-for-qt
