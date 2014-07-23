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


// util_runner.cpp

#include "util_runner.h"
#include <QDebug>
#include <QFinalState>

UtilRunner::UtilRunner(QString cmd, UtilWorker* util_worker, LogEmitter* err_emitter): \
    command_str(cmd),  worker(util_worker), \
    err_flag(err_emitter, SIGNAL(critical_message(QString))),\
    warn_flag(err_emitter, SIGNAL(warn_message(QString)))\
    {
}

void UtilRunner::run()
{
    worker->init();
    if(worker->is_valid()){
        Q_EMIT init_complete();
        worker->start();

        if( qApp->property("optn.verbose").toBool()){
            qDebug("Worker is done running.");
        }
        Q_EMIT result(0);
    }else{
        qWarning() << "Invalid preconditions.";
        Q_EMIT result(1);
    }
}


QString UtilRunner::command(){
    return QString(this->command_str);
}

bool UtilRunner::is_hidden(){
    QString run_silent_flag = worker->meta_lookup("silent");
    bool run_silent = ! run_silent_flag.isNull() || ! run_silent_flag.isEmpty();

    bool end_shown = err_flag.count() > 0;

    return run_silent && !end_shown;
}

void UtilRunner::request_cancel(){
    worker->exit_early();
}


QWidget* UtilRunner::worker_widget(){
    return (QWidget*)(worker->get_widget());
}

bool UtilRunner::has_widget(){
    return (!worker_widget_type().isEmpty()) && \
            worker->get_widget() != NULL;
}

QString UtilRunner::worker_widget_type(){
    return worker->meta_lookup("widget_type");
}

