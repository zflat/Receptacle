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
#include "hostwin_closer.h"

void HostwinCloser::end_curr_util(){
    if(host->get_main_window_obj()){
        host->get_main_window_obj()->close();
        Q_EMIT win_close_requested();
    }
    QTest::qWait(10);
    QTRY_VERIFY_WITH_TIMEOUT(!server->queue_busy(), 1000);
    Q_EMIT win_closed();
}
