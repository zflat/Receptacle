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

#ifndef TEST_UTILS_POPULATED_H
#define TEST_UTILS_POPULATED_H

#include <QString>
#include <QPointer>
#include <QtTest>


#include "util_collection.h"
#include "log_emitter.h"


class TestUtilsPopulated : public QObject
{
    Q_OBJECT

public:
    TestUtilsPopulated(): utils(NULL){}

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testPopulatedContains();
private:
    UtilCollection* utils;
    void verify_command(QString cmd);
    QPointer<LogEmitter>  logger;
};

#endif // TEST_UTILS_POPULATED_H
