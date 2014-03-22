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
