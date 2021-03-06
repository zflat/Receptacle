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

#include <QDateTime>
#include <QApplication>

#include "host_controller.h"

HostController::HostController(UtilCollection* u_collection, LogEmitter* log_emitter): \
    utils(u_collection),logger(log_emitter), main_window(NULL), bg_worker(NULL), \
    err_flag(logger, SIGNAL(critical_message(QString))),\
    fatal_flag(logger, SIGNAL(critical_message(QString))),\
    warn_flag(logger, SIGNAL(warn_message(QString)))\
    {}

void HostController::run_job(QString command){

    if( qApp->property("optn.verbose").toBool()){
        qDebug() << "Run job";
    }
    if(this->main_window != NULL){
        qWarning() << "Main window already allocated.";
    }
    this->main_window = new SelectLauncher();

    if( qApp->property("optn.verbose").toBool()){
        qDebug() << "Select launcher initialized";
    }
    this->main_window->populate_command_options(utils);
    this->main_window->connect_logger(this->logger);
    this->main_window->connect_errwarn_flag(&err_flag, &fatal_flag, &warn_flag);

    QObject::connect(this->main_window, SIGNAL(selected(QString)), this, SLOT(selected(QString)));
    QObject::connect(this->main_window, SIGNAL(close_requested()), this, SLOT(cancel_handler()));
    QObject::connect(this->main_window, SIGNAL(destroyed()), this, SLOT(job_cleanup()));

    // Log username and Date & Time
    // http://bytes.com/topic/c/answers/691168-username-caller
    qDebug() <<  LogEmitter::username().toStdString().c_str() \
             << QDateTime::currentDateTime().toString().toStdString().c_str();

    // Select the job (start running if command given)
    this->main_window->select_job(command);

    // open the main window
    this->main_window->show_me();
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
    qDebug() << "Selected" << cmd;
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
    UtilInterface* pluginUtil = NULL;

    if(pluginObj != NULL){
        if( qApp->property("optn.verbose").toBool()){
            qDebug()<<"Plugin found for given command.";
        }
        pluginUtil = qobject_cast<UtilInterface *>(pluginObj);
    }else{
        qWarning()<<"Plugin not found for the given command. Plugin unloaded....?";
        return;
    }

    if(!pluginUtil){return;}
    // plugin found

    if( qApp->property("optn.verbose").toBool()){
        qDebug()<<"Util constructed from given command.";
        qDebug() << pluginUtil->name().toStdString().c_str();
    }

    UtilWorker* worker = pluginUtil->newWorker();
    if( qApp->property("optn.verbose").toBool()){
        qDebug() << "Worker retrieval successful";
    }

    bg_worker = new UtilRunner(command, worker, logger);
    bg_worker->setAutoDelete(false);

    //QObject::connect(worker, SIGNAL(complete()), this, SLOT(job_complete_handler()),Qt::QueuedConnection);
    connect(bg_worker, SIGNAL(init_complete()), this, SLOT(plugin_setup()));
    connect(bg_worker, SIGNAL(result(int)), this, SLOT(job_complete_handler(int)));
    err_flag.reset_count();
    fatal_flag.reset_count();
    warn_flag.reset_count();
    //connect(err_flag, SIGNAL(signal_received())


    if( qApp->property("optn.verbose").toBool()){
        qDebug() << "Util Runner signal connect successful";
    }

    // notify that the bg worker is running
    main_window->set_is_running_bg(true);
    QThreadPool::globalInstance()->start(bg_worker);
}


void HostController::plugin_setup(){
    // Hide window if necessary
    if(bg_worker->is_hidden()){
        //main_window->hide();
        main_window->showMinimized();
    }

    // Add plugin widget to GUI if necessary
    if(bg_worker->has_widget()){
        if(!main_window->attach_widget(bg_worker->worker_widget(), bg_worker->worker_widget_type())){
            qCritical("Plugin widget indicated, but could not attach to the host UI.");
        }
    }

    Q_EMIT setup_complete();
}

void HostController::cancel_handler(){
    if(NULL != bg_worker ){
        // tell the bg worker to quit
        bg_worker->request_cancel();
    }else if(NULL != main_window){
        main_window->close();
    }
}


void HostController::job_complete_handler(int result){
    if(NULL == main_window){
        qCritical() << "Main window already closed before job completion processed.";
    }
    // notify that the job is not running
    main_window->set_is_running_bg(false);


    if( qApp->property("optn.verbose").toBool()){
        qDebug() << "job complete!(notified in ::job_complete_handler)";
    }

    /* Decide to close the main window or not
     *
     * Close the main window when UtilRunner indicates the utility
     * is hidden & the windows is minimized
     *
     * Close the main window when close has been requested.
     */
    bool should_close_window = false;

    if(main_window->get_is_pending_close()){
        qDebug() << "Window is pending close";
        should_close_window = true;
    }else if(bg_worker->is_hidden() && main_window->isMinimized()){
        qDebug() << "Silent utilty has not been shown by user";
        should_close_window = true;
    }

    if(should_close_window){

        if( qApp->property("optn.verbose").toBool()){
            qDebug("Should close window.");
        }
        if(main_window->get_is_pending_close()){
            qDebug("Main window is pending close");
        }
        if((bg_worker->is_hidden() && main_window->isMinimized())){
            qDebug("Hidden worker is minimzed");
        }
        main_window->close();
    }else{
        /*
         * Decide to notify error, warnings or success
         */
        if(fatal_flag.count()>0 || err_flag.count()>0){
            main_window->show_msg_level(QtCriticalMsg, true);
        }else if(warn_flag.count() > 0){
            main_window->show_msg_level(QtWarningMsg, true);
        }else{
            main_window->show_msg_level(QtDebugMsg, true);
        }
    }

    // TODO: Notify result after cleanup (so dispatcher does not release the mutex too early)
    Q_EMIT util_result(result);

    //
    // Program control waiting for window to close (if not closed above)
    //

}// job_complete_handler

void HostController::job_cleanup(){
    if( qApp->property("optn.verbose").toBool()){
        qDebug() << "closed window";
    }
    if(NULL != main_window){
       // delete main_window;
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
    if( qApp->property("optn.verbose").toBool()){
        qDebug() << "HostController cleanup complete";
    }
    Q_EMIT end_job(current_cmd);
}


