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
#include "log_emitter.h"


QPointer<LogEmitter> test_launcher_logger;
void test_launcher_log_handler_forwarder(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    if(test_launcher_logger)
        test_launcher_logger->publish_message(type, context, msg);

    printf("%s\n", msg.toStdString().c_str());
}


void TestLauncher::initTestCase()
{
    test_launcher_logger = new LogEmitter();
    qInstallMessageHandler(test_launcher_log_handler_forwarder);

    utils = new UtilCollection();
    host = new HostControllerDecorator(utils, test_launcher_logger);

    // Create an instance of a server and then start it.
    server = new Dispatcher(host);
    server->startServer();
    return;
}

void TestLauncher::cleanupTestCase()
{

    qDebug() << "Server cleanup";
    delete utils;
    delete host;
    delete server;
    qInstallMessageHandler(0);
}

void TestLauncher::testOpenCloseLauncher()
{
    server->queue_request("cmd");
    SelectLauncher* launcher = host->get_main_window();
    QVERIFY2(launcher, "Launcher is retrieved.");
    QVERIFY2(! launcher->isMinimized(), "Main window is not minimized");
    QVERIFY2(launcher->isVisible(), "Launcher is visible");
    host->kill_job();
    QTRY_VERIFY_WITH_TIMEOUT(!server->queue_busy(), 1000);
    QVERIFY2(true, "Failure");
    QVERIFY2(host->get_main_window() == NULL , "Main window is disposed");
}
