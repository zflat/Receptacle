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
}


void TestPrint::cleanupTestCase()
{
}


void TestPrint::init(){
    test_print_logger = new LogEmitter();
    qInstallMessageHandler(test_print_log_handler_forwarder);

    utils = new UtilCollection();
    host = new HostControllerDecorator(utils, test_print_logger);
    // Create an instance of a server and then start it.
    server = new Dispatcher(host);
    server->startServer();


    cmd = new CmdRunner(host, server);
    ender = new HostwinCloser(host, server);
}

void TestPrint::cleanup(){
    delete cmd;
    cmd = NULL;
    delete ender;
    ender = NULL;

    delete utils;
    delete host;
    delete server;
    delete test_print_logger;
    qInstallMessageHandler(0);
}

void TestPrint::testCommandPrint()
{
    QObject::connect(cmd, SIGNAL(command_completed()), ender, SLOT(end_curr_util()));
    for(int i=0; i<5; i++){
        QSignalSpy spy_win_closed(ender, SIGNAL(win_closed()));
        cmd->send_command("Print");
        QTest::qWait(50);
        QTRY_VERIFY_WITH_TIMEOUT(spy_win_closed.count() > 0, 1000);
    }
}

void TestPrint::testCommandDelayedPrint()
{
    QSignalSpy host_result(host, SIGNAL(util_result(int)));
    //QObject::connect(cmd, SIGNAL(command_completed()), ender, SLOT(end_curr_util()));
    server->queue_request("DelayedPrint");
    host->get_main_window_obj()->close();
    QTRY_VERIFY_WITH_TIMEOUT(host_result.count() < 1, 1000);
    QTest::qWait(500);
    QTRY_VERIFY_WITH_TIMEOUT(host_result.count() > 0, 1000);
}


void TestPrint::testWarnPrint(){
    QObject::connect(cmd, SIGNAL(ready4close()), ender, SLOT(end_curr_util()));
    QSignalSpy spy(cmd, SIGNAL(command_completed()));
    cmd->send_command("WarnPrint");

    QTRY_VERIFY_WITH_TIMEOUT(spy.count() > 0, 1000);
    QTest::qWait(10);
    QVERIFY2(host->get_main_window()->get_job_select_form()->get_select_box_style() == \
             JobSelectionForm::WARN_INDICATION_STYLE, "Selection box has WARN_INDICATION_STYLE");

    QSignalSpy spy_win_closed(ender, SIGNAL(win_closed()));
    cmd->ready4close();
    QTRY_VERIFY_WITH_TIMEOUT(spy_win_closed.count() > 0, 1000);
}

void TestPrint::testCriticalPrint(){
    QObject::connect(cmd, SIGNAL(ready4close()), ender, SLOT(end_curr_util()));
    cmd->send_command("CriticalPrint");
    // Check for color change to red
    QVERIFY2(host->get_main_window()->get_job_select_form()->get_select_box_style() == \
             JobSelectionForm::ERR_INDICATION_STYLE, "Selection box has ERR_INDICATION_STYLE");

    QSignalSpy spy_win_closed(ender, SIGNAL(win_closed()));
    cmd->ready4close();
    QTRY_VERIFY_WITH_TIMEOUT(spy_win_closed.count() > 0, 1000);
}



void TestPrint::testWarnCriticalSequence(){
    QObject::connect(cmd, SIGNAL(ready4close()), ender, SLOT(end_curr_util()));
    cmd->send_command("Print");

    QVERIFY2(host->get_main_window()->\
             get_job_select_form()->get_select_box_style().isEmpty(), "Selection box has no style");
    qWarning("Sending warning 1");
    QVERIFY2(host->get_main_window()->get_job_select_form()->get_select_box_style() == \
             JobSelectionForm::WARN_INDICATION_STYLE, "Selection box has WARN_INDICATION_STYLE");

    qCritical("Sending critical message 1");
    QVERIFY2(host->get_main_window()->get_job_select_form()->get_select_box_style() == \
             JobSelectionForm::ERR_INDICATION_STYLE, "Selection box has ERR_INDICATION_STYLE");

    qWarning("Sending warning message 2");
    QVERIFY2(host->get_main_window()->get_job_select_form()->get_select_box_style() == \
             JobSelectionForm::ERR_INDICATION_STYLE, "Selection box has ERR_INDICATION_STYLE");

    QSignalSpy spy_win_closed(ender, SIGNAL(win_closed()));
    cmd->ready4close();
    QTRY_VERIFY_WITH_TIMEOUT(spy_win_closed.count() > 0, 1000);
}
