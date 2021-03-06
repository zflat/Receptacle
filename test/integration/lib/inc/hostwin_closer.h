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


#ifndef HOSTWIN_CLOSER_H
#define HOSTWIN_CLOSER_H

#include <QString>
#include <QtTest>


#include "dispatcher.h"
#include "util_collection.h"
#include "host_controller_decorator.h"
#include "job_selection_form_decorator.h"
#include "select_launcher_decorator.h"
#include "log_emitter.h"


class HostwinCloser : public QObject
{
    Q_OBJECT

public:
   HostwinCloser(HostControllerDecorator* host_target, Dispatcher* server_target): \
        host(host_target), server(server_target){}

signals:
   void win_close_requested();
   void win_closed();

public Q_SLOTS:
   void end_curr_util();

private:
   HostControllerDecorator* host;
   Dispatcher* server;
   
};

#endif // HOSTWIN_CLOSER_H
