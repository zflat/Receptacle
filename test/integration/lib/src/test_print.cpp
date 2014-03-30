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
    qInstallMessageHandler(0);
}

void TestPrint::testCommandPrint()
{
    QObject::connect(cmd, SIGNAL(command_completed()), ender, SLOT(end_curr_util()));
    cmd->send_command("Print");
}

void TestPrint::testCommandDelayedPrint()
{
    QObject::connect(cmd, SIGNAL(command_completed()), ender, SLOT(end_curr_util()));
    cmd->send_command("DelayedPrint");
}

void TestPrint::testWarnPrint(){
    QObject::connect(cmd, SIGNAL(ready4close()), ender, SLOT(end_curr_util()));
    QSignalSpy spy(cmd, SIGNAL(command_completed()));
    cmd->send_command("WarnPrint");

    QTRY_VERIFY_WITH_TIMEOUT(spy.count() > 0, 1000);
    QTest::qWait(50);

    SelectLauncherDecorator* l = host->get_main_window();
    qDebug() << "Stylesheet:";
    qDebug() <<  l->styleSheet().toStdString().c_str();

    cmd->ready4close();

    // Check for color change to yellow
    /*
    selection_form = static_cast<JobSelectionFormDecorator*>(launcher->get_job_select_form());
    QVERIFY2(selection_form, "selection_form is retrieved.");

    selection_form->get_select_form_color();
    */
}

void TestPrint::testCriticalPrint(){
    QObject::connect(cmd, SIGNAL(ready4close()), ender, SLOT(end_curr_util()));
    cmd->send_command("CriticalPrint");

    // Check for color change to red

    cmd->ready4close();
}
