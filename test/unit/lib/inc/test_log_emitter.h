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
    void init();
    void cleanup();
private:
    LogEmitter* emitter;
    MessageSubscriber *info_sub;
    QString* info_message;

signals:
    void send_text(QString const message);
};

#endif //TEST_LOG_EMITTER_H
