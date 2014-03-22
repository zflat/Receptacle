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
    test_logger  = new LogEmitter();
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
    test_logger  = new LogEmitter();
    QObject::connect(test_logger, SIGNAL(info_message(QString)), info_sub, SLOT(set_message(QString)));
    QSignalSpy spy(test_logger, SIGNAL(info_message(QString)));
    QCOMPARE(spy.count(), 0);

    qInstallMessageHandler(test_log_handler_forwarder);
    qDebug() << info_message->toStdString().c_str();
    QCOMPARE(spy.count(), 1);
    qInstallMessageHandler(0);

    QVERIFY2(info_sub->getMessage()->compare(info_message) == 0, "Info message published and recieved.");
}

//  will be called before each test function is executed.
void TestLogEmitter::init()
{
    emitter = new LogEmitter();
    info_sub = new MessageSubscriber();
    QVERIFY2(info_sub->getMessage()->compare(info_sub->getMessage())==0, "String comparison works");

    QString* blank_str = new QString("");
    QVERIFY2(QString::compare(*info_sub->getMessage(), *blank_str)==0, "Initial message is blank");
    QVERIFY2(info_sub->getMessage()->compare(blank_str)==0, "Initial message is blank");

    info_message = new QString("INFO MESSAGE");
    delete blank_str;
}

// will be called after every test function.
void TestLogEmitter::cleanup()
{
    delete emitter;
    delete info_sub;
    delete info_message;
}
