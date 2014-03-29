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


#include "test_util_runner.h"
#include <QDebug>


void TestUtilRunner::test_constructor(){
    QVERIFY2(NULL == runner, "Runner is initialized to NULL");
    runner = new UtilRunner(cmd, worker, error_notifier);
    QVERIFY2(NULL != runner, "Runner is constructed and is not NULL");
}

void TestUtilRunner::test_is_silent_end(){
    QVERIFY2(NULL == runner, "Runner is initialized to NULL");
    runner = new UtilRunner(cmd, worker, error_notifier);
    QVERIFY2(! runner->is_hidden(), "A default Runner is not hidden");
    delete runner;

    worker->set_is_silent(false);
    runner = new UtilRunner(cmd, worker, error_notifier);
    QVERIFY2(! runner->is_hidden(), "A non-silent Runner is not hidden");
    delete runner;

    worker->set_is_silent(true);
    runner = new UtilRunner(cmd, worker, error_notifier);
    QVERIFY2(runner->is_hidden(), "A silent Runner is hidden");
    QMessageLogContext context;
    error_notifier->publish_message(QtCriticalMsg, context, "Sending error message");
    QVERIFY2(!runner->is_hidden(), "A silent Runner is shown after error is thrown");
}

void TestUtilRunner::init(){
  runner = NULL;
  error_notifier = new LogEmitter();
  // UtilTestWorker* worker = new UtilTestWorker();
  worker = new UtilTestWorker();
  cmd = QString("");
}

void TestUtilRunner::cleanup(){
    delete runner;
    delete error_notifier;
    delete worker;
}
