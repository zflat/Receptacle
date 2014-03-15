#include "widgets/log_text.h"
#include "test_log_text_page.h"

#include <QMainWindow>

void TestLogTextPage::constructor(){
    // CASE: default
    QMainWindow* win = new QMainWindow();
    qDebug() << "Default constructor";
    LogTextPage* page = new LogTextPage(win);
    QVERIFY2(page != NULL, "LogTextPage constructor returns non null");
}


void TestLogTextPage::initTestCase()
{
}


void TestLogTextPage::cleanupTestCase()
{

}
