#ifndef TEST_LOG_TEXT_PAGE_H
#define TEST_LOG_TEXT_PAGE_H

#include <QtTest/QTest>
#include <QtWidgets>

class TestLogTextPage : public QObject{
 Q_OBJECT
private slots:
    void constructor();
    void initTestCase();
    void cleanupTestCase();
};

#endif //TEST_LOG_TEXT_PAGE_H
