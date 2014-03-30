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



#include "test_launcher.h"


TestLauncher::TestLauncher()
{
}

void TestLauncher::initTestCase()
{
    UtilCollection* utils = new UtilCollection();
    LogEmitter* logger = new LogEmitter();
    host = new HostControllerDecorator(utils, logger);

    // Create an instance of a server and then start it.
    server = new Dispatcher(host);
    server->startServer();
    return;
}

void TestLauncher::cleanupTestCase()
{
    qDebug() << "Server cleanup";
    delete server;
}

void TestLauncher::testOpenCloseLauncher()
{
    server->queue_request("cmd");
    QVERIFY2(! host->get_main_window()->isMinimized(), "Main window is not minimized");
    host->kill_job();
    QTRY_VERIFY_WITH_TIMEOUT(!server->queue_busy(), 1000);
    QVERIFY2(true, "Failure");
    QVERIFY2(host->get_main_window() == NULL , "Main window is disposed");
}
