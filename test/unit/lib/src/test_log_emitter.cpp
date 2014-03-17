#include "test_log_emitter.h"
#include "message_subscriber.h"
#include <QtGlobal>
#include <QDebug>
#include <QCoreApplication>
#include <QMessageLogContext>

void TestLogEmitter::testPublishMessage(){
    QObject::connect(emitter, SIGNAL(info_message(QString)), info_sub, SLOT(set_message(QString)));
    QMessageLogContext context;

    emitter->publish_message(QtDebugMsg, context, info_message->toStdString().c_str());
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
