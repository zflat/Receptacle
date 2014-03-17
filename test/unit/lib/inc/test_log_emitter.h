#ifndef TEST_LOG_EMITTER_H
#define TEST_LOG_EMITTER_H

#include <QtTest/QTest>
#include <QtWidgets>

#include "log_emitter.h"

class TestLogEmitter : public QObject{
 Q_OBJECT
private slots:
    void testPublishMessage();
    void initTestCase();
    void cleanupTestCase();
private:
    LogEmitter* emitter;
signals:
    void send_text(QString const message);
};

#endif //TEST_LOG_EMITTER_H
