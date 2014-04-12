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



#include "test_launcher.h"
#include "log_emitter.h"

#include <QTestKeyEvent>

QPointer<LogEmitter> test_launcher_logger;
void test_launcher_log_handler_forwarder(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    if(test_launcher_logger)
        test_launcher_logger->publish_message(type, context, msg);

    printf("%s\n", msg.toStdString().c_str());
}


void TestLauncher::initTestCase()
{
    test_launcher_logger = new LogEmitter();
    //qInstallMessageHandler(test_launcher_log_handler_forwarder);

    utils = new UtilCollection();
    host = new HostControllerDecorator(utils, test_launcher_logger);

    // Create an instance of a server and then start it.
    server = new Dispatcher(host);
    server->startServer();
    return;
}

void TestLauncher::cleanupTestCase()
{

    qDebug() << "Server cleanup";
    delete utils;
    delete host;
    delete server;
    //qInstallMessageHandler(0);
}

void TestLauncher::testOpenCloseLauncher()
{
    server->queue_request("cmd");
    SelectLauncher* launcher = host->get_main_window();
    QVERIFY2(launcher, "Launcher is retrieved.");
    QVERIFY2(! launcher->isMinimized(), "Main window is not minimized");
    QVERIFY2(launcher->isVisible(), "Launcher is visible");
    launcher->close();

    QTRY_VERIFY_WITH_TIMEOUT(!server->queue_busy(), 1000);
    QVERIFY2(true, "Failure");
    QVERIFY2(host->get_main_window() == NULL , "Main window is disposed");
}


void TestLauncher::testKeyboardQuitLauncher()
{
#if defined(Q_OS_WIN)
    return;
#endif
    for(int i=0; i<3; i++){
        server->queue_request("Print");
        SelectLauncherDecorator* launcher = host->get_main_window();
        QVERIFY2(launcher, "Launcher is retrieved.");
        QTest::qWaitForWindowActive(launcher);
        QVERIFY2(! launcher->isMinimized(), "Main window is not minimized");
        QVERIFY2(launcher->isVisible(), "Launcher is visible");
        QTRY_VERIFY_WITH_TIMEOUT(server->queue_busy(), 100);

        qDebug() << "Send Ctrl+Q try";
        QKeyEvent key(QEvent::KeyPress, 'Q', (Qt::KeyboardModifier)Qt::CTRL);
        QApplication::sendEvent(launcher, &key);
        QVERIFY2(key.isAccepted(), "Key Ctrl+Q is accepted");

        QTRY_VERIFY_WITH_TIMEOUT(!server->queue_busy(), 1000);
        QVERIFY2(true, "Failure");
        QVERIFY2(host->get_main_window() == NULL , "Main window is disposed");
        qDebug() << "Iteration complete.";
    } // for()
}


void TestLauncher::testMenuQuitLauncher()
{
#if defined(Q_OS_WIN)
    return;
#endif
    for(int i=0; i<15; i++){
        QVERIFY2(NULL == host->get_main_window(), "No window before sending request.");
        server->queue_request("Print");
        SelectLauncherDecorator* launcher = host->get_main_window();
        QVERIFY2(launcher, "Launcher is retrieved.");
        QTest::qWaitForWindowActive(launcher);
        QVERIFY2(! launcher->isMinimized(), "Main window is not minimized");
        QVERIFY2(launcher->isVisible(), "Launcher is visible");
        QTRY_VERIFY_WITH_TIMEOUT(server->queue_busy(), 100);

        qDebug() << "Press Alt+F";
        QKeyEvent key_altF(QEvent::KeyPress, 'F', (Qt::KeyboardModifier)Qt::ALT);
        QApplication::sendEvent(launcher, &key_altF);
        QTRY_VERIFY_WITH_TIMEOUT(key_altF.isAccepted(), 500);

        if(false){
            QTest::mouseClick(launcher->get_menu_file(), Qt::LeftButton, 0, QPoint(0, 1), 500);
            QTest::qWait(50);
        }
        else if(launcher && launcher->isActiveWindow()){
            qDebug() << "Press x";
            QTest::keyPress(launcher->get_menu_file(), 'x');
        }else{
            QKeyEvent key_x(QEvent::KeyPress, 'x', (Qt::KeyboardModifier)0);
            QApplication::sendEvent(launcher->get_menu_file(), &key_x);
            QTRY_VERIFY_WITH_TIMEOUT(key_x.isAccepted(), 500);
        }

        QTRY_VERIFY_WITH_TIMEOUT(!server->queue_busy(), 1000);
        QVERIFY2(host->get_main_window() == NULL , "Main window is disposed");
        qDebug() << "Iteration complete.";
    } // for()
}
