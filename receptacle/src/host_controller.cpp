#include "host_controller.h"

HostController::HostController(UtilCollection* u_collection): utils(u_collection){}

void HostController::run_job(QString command){
    if(!utils->has_command(command)){
         qWarning() << "Command not recognized: " << command.toStdString().c_str();
        return;
    }
    // command is recognized

    QObject* plugin = utils->util(command);
    UtilInterface *iUtil = qobject_cast<UtilInterface *>(plugin);
    if(!iUtil){return;}
    // plugin found

    iUtil->run_util();


    // Time consumer
    MyTask *mytask = new MyTask();
    mytask->setAutoDelete(true);

    // using queued connection
    connect(mytask, SIGNAL(Result(int)), this, SLOT(TaskResult(int)), Qt::QueuedConnection);

    qDebug() << "Starting a new task using a thread from the QThreadPool";

    // QThreadPool::globalInstance() returns global QThreadPool instance
    QThreadPool::globalInstance()->start(mytask);

    return;
}
