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



#include "test_utils_populated.h"
#include "log_emitter.h"


QPointer<LogEmitter> test_util_populated_logger;
void test_util_populated_log_handler_forwarder(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    if(test_util_populated_logger)
        test_util_populated_logger->publish_message(type, context, msg);

    printf("%s\n", msg.toStdString().c_str());
}


void TestUtilsPopulated::initTestCase()
{
    utils = new UtilCollection();
    test_util_populated_logger = new LogEmitter();
    qInstallMessageHandler(test_util_populated_log_handler_forwarder);
}

void TestUtilsPopulated::cleanupTestCase()
{
    if(NULL != utils)
        delete utils;

    qInstallMessageHandler(0);
}

void TestUtilsPopulated::testPopulatedContains()
{
    verify_command("Sleepy");
    verify_command("Print");
    verify_command("DelayedPrint");
    verify_command("WarnPrint");
    verify_command("CriticalPrint");
    verify_command("FatalPrint");
    verify_command("InvalidPrint");
    verify_command("HelloBye");
    verify_command("SimpleForm");
    verify_command("ComplexForm");
    verify_command("ThatNeverEnds");
}

void TestUtilsPopulated::verify_command(QString cmd){
    QVERIFY2(NULL != utils, "UtilsCollection initialized");
    QVERIFY2(utils->has_command(cmd), QString(cmd + " command is recognized").toStdString().c_str());
}
