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


#include "select_launcher_decorator.h"
#include "widgets/select_launcher.h"
#include "cmd_runner.h"

void CmdRunner::send_command(QString cmd){
    QSignalSpy host_result(host, SIGNAL(util_result(int)));
    server->queue_request(cmd);
    QTest::qWait(10);
    QTRY_VERIFY_WITH_TIMEOUT(host_result.count() > 0, 1000);
    QTest::qWait(10);

    SelectLauncher* launcher_obj;
    QTRY_VERIFY_WITH_TIMEOUT(launcher_obj = host->get_main_window_obj(), 1000);
    QVERIFY2(launcher_obj, "Launcher obj is retrieved.");

    SelectLauncherDecorator* launcher = host->get_main_window();
    QVERIFY2(launcher, "Launcher is retrieved.");
    QTRY_VERIFY_WITH_TIMEOUT(launcher, 100);

    Q_EMIT command_completed();
}

/*
void CmdRunner::end_curr_util(){
    Q_EMIT ready4close();
}
*/
