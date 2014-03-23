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


#ifndef TEST_LOG_EMITTER_H
#define TEST_LOG_EMITTER_H

#include <QtTest/QTest>
#include <QtWidgets>

#include "log_emitter.h"
#include "message_subscriber.h"

class TestLogEmitter : public QObject{
 Q_OBJECT
private slots:
    void testPublishMessage();
    void testMessageHandler();
    void testContinuityLevels();
    void init();
    void cleanup();
private:
    LogEmitter* emitter;
    MessageSubscriber *info_sub;
    MessageSubscriber *warn_sub;
    MessageSubscriber *critical_sub;
    MessageSubscriber *fatal_sub;
    QString* info_message;
    QString* warn_message;
    QString* critical_message;
    QString* fatal_message;

signals:
    void send_text(QString const message);
};

#endif //TEST_LOG_EMITTER_H
