#include "widgets/log_text.h"
#include "test_log_text_page.h"

#include <QMainWindow>

void TestLogTextPage::testConstructor(){
    // CASE: default
    QMainWindow* win = new QMainWindow();
    qDebug() << "Default constructor";
    LogTextPage* page = new LogTextPage(win);
    QVERIFY2(page != NULL, "LogTextPage constructor returns non null");
    QVERIFY2(page->text_area != NULL, "LogTextPage constructor creates a text_area");
    qDebug() << "Constructor success";
}

void TestLogTextPage::testAppendTextSlot(){
    LogTextPage* page = new LogTextPage();
    QVERIFY2(page->text_area->toPlainText() == "", "Plain text is initially blank");
    QObject::connect(this, &TestLogTextPage::send_text, page, &LogTextPage::appendText);
    QString test_str = "TESTSTR";
    emit send_text(test_str);
    QVERIFY2(page->text_area->toPlainText() == test_str, "Plain text must match the test_str value");
}


void TestLogTextPage::initTestCase()
{
}


void TestLogTextPage::cleanupTestCase()
{

}
