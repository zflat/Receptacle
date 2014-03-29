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



#ifndef TEST_UTIL_RUNNER_H
#define TEST_UTIL_RUNNER_H

#include <QtTest/QTest>
#include "util_runner.h"
#include "util_test_worker.h"
#include "log_emitter.h"

class TestUtilRunner : public QObject{
 Q_OBJECT
private slots:
    void test_constructor();
    void test_is_silent_end();
    void init();
    void cleanup();
private:
    UtilRunner* runner;
    LogEmitter* error_notifier;
    UtilTestWorker* worker;
    QString cmd;
};

#endif //TEST_UTIL_RUNNER_H
