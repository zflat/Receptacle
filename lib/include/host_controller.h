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



#ifndef HOST_CONTROLLER_H
#define HOST_CONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QThreadPool>
#include "util_runner.h"
#include "util_collection.h"
#include "widgets/select_launcher.h"
#include "log_emitter.h"

class HostController : public QObject
{
    Q_OBJECT
public:
    HostController(UtilCollection* u_collection, LogEmitter* log_emitter);
    void run_job(QString command);
    void kill_job();
    void notify_block();

signals:
    void end_job(QString cmd);

public slots:
    void selected(QString cmd);

protected:
    UtilCollection* utils;
    LogEmitter* logger;
    SelectLauncher* main_window;
    UtilInterface* current_util;
    UtilRunner* bg_worker;

protected slots:
       void exec_plugin(QString command);
       void cancel_handler();
       void job_complete_handler();
};

#endif // HOST_CONTROLLER_H
