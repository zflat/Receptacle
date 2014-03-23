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


#include "test_log_emitter.h"
#include "message_subscriber.h"
#include <QtGlobal>
#include <QDebug>
#include <QCoreApplication>
#include <QMessageLogContext>
#include <QSignalSpy>


QPointer<LogEmitter> test_logger;
void test_log_handler_forwarder(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    if(test_logger)
        test_logger->publish_message(type, context, msg);
    else
        printf("%s\n", msg.toStdString().c_str());
}


void TestLogEmitter::testPublishMessage(){
    QMessageLogContext context;
    if(test_logger != NULL){
        QVERIFY(test_logger);
        QObject::connect(test_logger, SIGNAL(info_message(QString)), info_sub, SLOT(set_message(QString)));
        test_logger->publish_message(QtDebugMsg, context, info_message->toStdString().c_str());
    }else{
        QVERIFY(!test_logger);
        QObject::connect(emitter, SIGNAL(info_message(QString)), info_sub, SLOT(set_message(QString)));
        emitter->publish_message(QtDebugMsg, context, info_message->toStdString().c_str());
    }
    QVERIFY2(info_sub->getMessage()->compare(info_message) == 0, "Info message published and recieved.");
}


void TestLogEmitter::testMessageHandler(){
    QObject::connect(test_logger, SIGNAL(info_message(QString)), info_sub, SLOT(set_message(QString)));
    QSignalSpy spy(test_logger, SIGNAL(info_message(QString)));
    QCOMPARE(spy.count(), 0);

    qDebug() << info_message->toStdString().c_str();
    QCOMPARE(spy.count(), 1);
    QVERIFY2(info_sub->getMessage()->compare(info_message) == 0, "Info message published and recieved.");
}


void TestLogEmitter::testContinuityLevels(){
    QString msg;
    QObject::connect(test_logger, SIGNAL(info_message(QString)), info_sub, SLOT(set_message(QString)));
    QObject::connect(test_logger, SIGNAL(warn_message(QString)), warn_sub, SLOT(set_message(QString)));
    QObject::connect(test_logger, SIGNAL(critical_message(QString)), critical_sub, SLOT(set_message(QString)));
    QObject::connect(test_logger, SIGNAL(fatal_message(QString)), fatal_sub, SLOT(set_message(QString)));

    qDebug() << info_message->toStdString().c_str();
    QVERIFY2(info_sub->getMessage()->compare(info_message) == 0, "Info message published and recieved.");
    QVERIFY2(info_sub->getMessage()->compare(warn_message) != 0, "Discontinuity with message type exepcted.");
    QVERIFY2(info_sub->getMessage()->compare(critical_message) != 0, "Discontinuity with message type exepcted.");
    QVERIFY2(info_sub->getMessage()->compare(fatal_message) != 0, "Discontinuity with message type exepcted.");

    qWarning() << warn_message->toStdString().c_str();
    msg = warn_sub->getMessage()->section('\n', 1, 1);
    QVERIFY2(msg.compare(warn_message) == 0, "Warn message published and recieved.");
    QVERIFY2(msg.compare(info_message) != 0, "Discontinuity with message type exepcted.");
    QVERIFY2(msg.compare(critical_message) != 0, "Discontinuity with message type exepcted.");
    QVERIFY2(msg.compare(fatal_message) != 0, "Discontinuity with message type exepcted.");

    qCritical() << critical_message->toStdString().c_str();
    msg = critical_sub->getMessage()->section('\n', 1, 1);
    QVERIFY2(msg.compare(critical_message) == 0, "Critical message published and recieved.");
    QVERIFY2(msg.compare(info_message) != 0, "Discontinuity with message type exepcted.");
    QVERIFY2(msg.compare(warn_message) != 0, "Discontinuity with message type exepcted.");
    QVERIFY2(msg.compare(fatal_message) != 0, "Discontinuity with message type exepcted.");

    if(false){
        qFatal(fatal_message->toStdString().c_str());
        QVERIFY2(fatal_sub->getMessage()->compare(fatal_message) == 0, "Fatal message published and recieved.");
    }
}

//  will be called before each test function is executed.
void TestLogEmitter::init()
{
    test_logger  = new LogEmitter();
    emitter = new LogEmitter();
    info_sub = new MessageSubscriber();
    QVERIFY2(info_sub->getMessage()->compare(info_sub->getMessage())==0, "String comparison works");

    warn_sub = new MessageSubscriber();
    critical_sub = new MessageSubscriber();
    fatal_sub = new MessageSubscriber();

    QString* blank_str = new QString("");
    QVERIFY2(QString::compare(*info_sub->getMessage(), *blank_str)==0, "Initial message is blank");
    QVERIFY2(info_sub->getMessage()->compare(blank_str)==0, "Initial message is blank");

    info_message = new QString("INFO MESSAGE");
    warn_message = new QString("WARN MESSAGE");
    critical_message = new QString("CRITICAL MESSAGE");
    fatal_message = new QString("FATAL MESSAGE");
    delete blank_str;

    qInstallMessageHandler(test_log_handler_forwarder);
}

// will be called after every test function.
void TestLogEmitter::cleanup()
{
    delete test_logger;
    delete emitter;
    delete info_sub;
    delete warn_sub;
    delete critical_sub;
    delete fatal_sub;
    delete info_message;
    delete warn_message;
    delete critical_message;
    delete fatal_message;
    qInstallMessageHandler(0);
}
