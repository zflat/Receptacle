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

#ifndef TEST_LAUNCHER_H
#define TEST_LAUNCHER_H

#include "dispatcher.h"
#include "util_collection.h"
#include "host_controller_decorator.h"
#include "log_emitter.h"


class TestLauncher : public QObject
{
    Q_OBJECT

public:
    //TestLauncher(QPointer<LogEmitter> logger_ref): logger(logger_ref){}
    TestLauncher(){}

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testOpenCloseLauncher();
    void testKeyboardQuitLauncher();
    void testMenuQuitLauncher();
private:
    Dispatcher* server;
    HostControllerDecorator* host;
    UtilCollection* utils;
    QPointer<LogEmitter>  logger;
};

#endif // TEST_LAUNCHER_H
