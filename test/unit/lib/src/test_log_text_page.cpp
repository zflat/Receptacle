#include "widgets/log_text.h"
#include "test_log_text_page.h"

#include <QMainWindow>

void TestLogText::testConstructor(){
    // CASE: default
    QMainWindow* win = new QMainWindow();
    qDebug() << "Default constructor";
    LogText* page = new LogText(win);
    QVERIFY2(page != NULL, "LogTextPage constructor returns non null");
    QVERIFY2(page->text_area() != NULL, "LogTextPage constructor creates a text_area");
    qDebug() << "Constructor success";
}

void TestLogText::testAppendTextSlot(){
    LogText* log = new LogText();
    QVERIFY2(log->text_area()->toPlainText() == "", "Plain text is initially blank");
    QObject::connect(this, &TestLogText::send_text, log, &LogText::appendText);
    QString test_str = "TESTSTR";
    emit send_text(test_str);
    QVERIFY2(log->text_area()->toPlainText() == test_str, "Plain text must match the test_str value");
}
