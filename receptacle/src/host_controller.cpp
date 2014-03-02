#include "host_controller.h"
#include "util_worker.h"

HostController::HostController(UtilCollection* u_collection): utils(u_collection){}

void HostController::run_job(QString command){
    if(this->main_window != NULL){
        qWarning() << "Main window already allocated.";
    }
    this->main_window = new SelectLauncher();
    this->main_window->populate_command_options(utils);
    QObject::connect(this->main_window, SIGNAL(selected(QString)), this, SLOT(selected(QString)));
    this->main_window->select_job(command);
    QObject::connect(this->main_window, SIGNAL(close_sig()), this, SLOT(cancel_handler()));

    // open the main window
    this->main_window->showNormal();
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
    }else{
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

    UtilWorker* worker = (UtilWorker *)(pluginUtil);
    qDebug() << "Worker cast successful";
    // QObject::connect(worker, SIGNAL(complete()), this, SLOT(job_complete_handler()),Qt::QueuedConnection);
    // qDebug() << "Worker signale connect successful";

    worker->run();

    //pluginUtil->worker->setAutoDelete(true);
    //QObject::connect(pluginObj, SIGNAL(complete()), this, SLOT(job_complete_handler()),Qt::QueuedConnection);
    //QThreadPool::globalInstance()->start(pluginUtil->worker);


/*
        // Time consumer
        MyTask *mytask = new MyTask();
        mytask->setAutoDelete(true);

        // using queued connection
        //connect(mytask, SIGNAL(Result(int)), this, SLOT(TaskResult(int)), Qt::QueuedConnection);
        QObject::connect(mytask, SIGNAL(Result(int)), this, SLOT(job_complete_handler()), Qt::QueuedConnection);

        qDebug() << "Starting a new task using a thread from the QThreadPool";

        // QThreadPool::globalInstance() returns global QThreadPool instance
        QThreadPool::globalInstance()->start(mytask);
*/
}

void HostController::cancel_handler(){
    qDebug() << "closed window";
    delete this->main_window;
    this->main_window = NULL;
    end_job(NULL);
}

void HostController::job_complete_handler(){
    qDebug() << "job complete!(notified in signal handler)";
}
