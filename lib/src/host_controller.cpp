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

#include "host_controller.h"
#include <QDateTime>

HostController::HostController(UtilCollection* u_collection, LogEmitter* log_emitter): \
    utils(u_collection),logger(log_emitter), bg_worker(NULL){}

void HostController::run_job(QString command){
    if(this->main_window != NULL){
        qWarning() << "Main window already allocated.";
    }
    this->main_window = new SelectLauncher();
    this->main_window->populate_command_options(utils);
    this->main_window->connect_logger(this->logger);
    QObject::connect(this->main_window, SIGNAL(selected(QString)), this, SLOT(selected(QString)));
    QObject::connect(this->main_window, SIGNAL(close_requested()), this, SLOT(cancel_handler()));
    QObject::connect(this->main_window, SIGNAL(close_sig()), this, SLOT(job_cleanup()));

    this->main_window->select_job(command);
    // open the main window

    // Log username
    // http://bytes.com/topic/c/answers/691168-username-caller
    // Log Date and time
    qDebug()<< QDateTime::currentDateTime().toString().toStdString().c_str();

    this->main_window->showNormal();
} // run_job


void HostController::kill_job(){
    cancel_handler();
    /*
    if(this->bg_worker != NULL){
        if(this->thread() != NULL){
            this->thread()->terminate();
            this->thread()->wait();
        }
        delete bg_worker;
        this->bg_worker = NULL;
    }
    this->main_window->close();
    */
}

void HostController::notify_block(){

}

void HostController::selected(QString cmd){
    qWarning() << "selected..";
    exec_plugin(cmd);
}

void HostController::exec_plugin(QString command){
    if(command == NULL || command == ""){
        return;
    }

    // select the specified command
    if(utils->has_command(command)){
        // command is recognized
    }else if(command.isEmpty()){
        qDebug() << tr("No command specified.");
    }
    else{
        qWarning() << "Command not recognized: " << command.toStdString().c_str();
    }

    QObject* pluginObj = utils->util(command);
    if(pluginObj != NULL){
        qDebug()<<"Plugin found for given command.";
    }else{
        qWarning()<<"Plugin unloaded....?";
    }
    UtilInterface* pluginUtil = qobject_cast<UtilInterface *>(pluginObj);
    // UtilWorker* pluginUtil = qobject_cast<UtilWorker *>(pluginObj);
    qDebug()<<"Util constructed from given command.";
    if(!pluginUtil){return;}
    // plugin found

    qDebug() << pluginUtil->name().toStdString().c_str();

    UtilWorker* worker = pluginUtil->newWorker();
    qDebug() << "Worker retrieval successful";


    bg_worker = new UtilRunner(command, worker, logger);
    bg_worker->setAutoDelete(false);

    //QObject::connect(worker, SIGNAL(complete()), this, SLOT(job_complete_handler()),Qt::QueuedConnection);
    connect(bg_worker, SIGNAL(result(int)), this, SLOT(job_complete_handler(int)));
    qDebug() << "Util Runner signal connect successful";

    // notify that the bg worker is running
    main_window->set_is_running_bg(true);
    QThreadPool::globalInstance()->start(bg_worker);
}

void HostController::cancel_handler(){
    if(NULL != bg_worker ){
        // tell the bg worker to quit
        bg_worker->request_cancel();
    }else if(NULL != main_window){
        main_window->close();
    }
}

void HostController::job_cleanup(){
    qDebug() << "closed window";
    if(NULL != main_window){
        delete main_window;
        main_window = NULL;
    }
    QString current_cmd;
    if(NULL != bg_worker){
        current_cmd = bg_worker->command();
        delete bg_worker;
        bg_worker = NULL;
    }else{
        current_cmd = "";
    }
    Q_EMIT end_job(current_cmd);
    qDebug() << "HostController cleanup complete";
}

void HostController::job_complete_handler(int result){
    // notify that the job is not running
    main_window->set_is_running_bg(false);
    Q_EMIT util_result(result);

    qDebug() << "job complete!(notified in signal handler)";

    /* Decide to close the main window or not
     *
     * Close the main window when UtilRunner indicates the utility
     * is hidden & the windows is minimized
     *
     * Close the main window when close has been requested.
     */
    bool should_close_window = main_window->get_is_pending_close() ||
            (bg_worker->is_hidden() && main_window->isMinimized());

    if(should_close_window){
        main_window->close();
    }
}
