/*

Copyright 2014 William Wedler

This file is part of Receptacle

Receptacle is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Receptacle is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Receptacle.  If not, see <http://www.gnu.org/licenses/>.

*/


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
