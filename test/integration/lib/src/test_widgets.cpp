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



#include "test_widgets.h"
#include "log_emitter.h"


QPointer<LogEmitter> test_widgets_logger;
void test_widgets_log_handler_forwarder(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    if(test_widgets_logger)
        test_widgets_logger->publish_message(type, context, msg);

    printf("%s\n", msg.toStdString().c_str());
}


void TestWidgets::initTestCase()
{
}


void TestWidgets::cleanupTestCase()
{
}


void TestWidgets::init(){
    test_widgets_logger = new LogEmitter();
    qInstallMessageHandler(test_widgets_log_handler_forwarder);

    utils = new UtilCollection();
    host = new HostControllerDecorator(utils, test_widgets_logger);
    // Create an instance of a server and then start it.
    server = new Dispatcher(host);
    server->startServer();


    cmd = new CmdRunner(host, server);
    ender = new HostwinCloser(host, server);
}

void TestWidgets::cleanup(){
    delete cmd;
    cmd = NULL;
    delete ender;
    ender = NULL;

    delete utils;
    delete host;
    delete server;
    delete test_widgets_logger;
    qInstallMessageHandler(0);
}


void TestWidgets::testNoWidget(){
    cmd->send_command("Print");

    QVERIFY2(NULL == host->get_main_window()->get_plugin_widget(), \
             "No widget for plugin without a widget.");

    QSignalSpy spy_win_closed(ender, SIGNAL(win_closed()));
    ender->end_curr_util();
    QTRY_VERIFY_WITH_TIMEOUT(spy_win_closed.count() > 0, 1000);
}
