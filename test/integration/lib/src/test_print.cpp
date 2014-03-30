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



#include "test_print.h"
#include "log_emitter.h"


QPointer<LogEmitter> test_print_logger;
void test_print_log_handler_forwarder(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    if(test_print_logger)
        test_print_logger->publish_message(type, context, msg);

    printf("%s\n", msg.toStdString().c_str());
}




void TestPrint::initTestCase()
{
    test_print_logger = new LogEmitter();
    qInstallMessageHandler(test_print_log_handler_forwarder);
    utils = new UtilCollection();

    host = new HostControllerDecorator(utils, test_print_logger);
    // Create an instance of a server and then start it.
    server = new Dispatcher(host);
    server->startServer();
    return;
}

void TestPrint::cleanupTestCase()
{
    delete utils;
    delete host;
    delete server;
    qInstallMessageHandler(0);
}

void TestPrint::testCommandPrint()
{
    send_print_command("Print");
    end_print_util();
}

void TestPrint::send_print_command(QString cmd){
      QSignalSpy host_result(host, SIGNAL(util_result(int)));
      server->queue_request(cmd);
      QTest::qWait(10);
      QTRY_VERIFY_WITH_TIMEOUT(host_result.count() > 0, 1000);
      QTest::qWait(10);
/*
      SelectLauncher* launcher_obj = host->get_main_window_obj();
      QTRY_VERIFY_WITH_TIMEOUT(launcher_obj, 100);
      QVERIFY2(launcher_obj, "Launcher obj is retrieved.");

      launcher = host->get_main_window();
      QVERIFY2(launcher, "Launcher is retrieved.");
      QTRY_VERIFY_WITH_TIMEOUT(launcher, 100);
*/
}

void TestPrint::end_print_util(){
    if(host->get_main_window_obj())
        host->get_main_window_obj()->close();
    QTest::qWait(10);
    QTRY_VERIFY_WITH_TIMEOUT(!server->queue_busy(), 1000);
}

void TestPrint::testCommandDelayedPrint()
{
    send_print_command("DelayedPrint");
    end_print_util();
}



void TestPrint::testWarnPrint(){
    send_print_command("WarnPrint");

    // Check for color change to yellow
    /*
    selection_form = static_cast<JobSelectionFormDecorator*>(launcher->get_job_select_form());
    QVERIFY2(selection_form, "selection_form is retrieved.");

    selection_form->get_select_form_color();
*/
    end_print_util();
}


void TestPrint::testCriticalPrint(){
    send_print_command("CriticalPrint");

    // Check for color change to red

    end_print_util();
}
