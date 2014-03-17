#include "test_log_emitter.h"
#include "message_subscriber.h"
#include <QtGlobal>

void TestLogEmitter::testPublishMessage(){
    MessageSubscriber * info_sub = new MessageSubscriber();
    QVERIFY2(info_sub->getMessage()->compare(info_sub->getMessage())==0, "String comparison works");

    QString* blank_str = new QString("");
    QVERIFY2(QString::compare(*info_sub->getMessage(), *blank_str)==0, "Initial message is blank");
    QVERIFY2(info_sub->getMessage()->compare(blank_str)==0, "Initial message is blank");


    QObject::connect(this->emitter, SIGNAL(info_message(QString)), info_sub, SLOT(set_message(QString)));
    QString* info_message = new QString("INFO MESSAGE");

    this->emitter->publish_message(QtDebugMsg, info_message->toStdString().c_str());
    QVERIFY2(info_sub->getMessage()->compare(info_message) == 0, "Info message published and recieved.");
}

void TestLogEmitter::initTestCase()
{
    this->emitter = new LogEmitter();
}


void TestLogEmitter::cleanupTestCase()
{

}
