#ifndef TEST_LOG_TEXT_PAGE_H
#define TEST_LOG_TEXT_PAGE_H

#include <QtTest/QTest>
#include <QtWidgets>

class TestLogTextPage : public QObject{
 Q_OBJECT
private slots:
    void testConstructor();
    void testAppendTextSlot();
    void initTestCase();
    void cleanupTestCase();
signals:
    void send_text(QString message);
};

#endif //TEST_LOG_TEXT_PAGE_H
