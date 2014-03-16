#ifndef TEST_LOG_EMITTER_H
#define TEST_LOG_EMITTER_H

#include <QtTest/QTest>
#include <QtWidgets>

class TestLogEmitter : public QObject{
 Q_OBJECT
private slots:
    void testForwardMessage();
    void initTestCase();
    void cleanupTestCase();
signals:
    void send_text(QString message);
};

#endif //TEST_LOG_EMITTER_H
