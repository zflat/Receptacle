#include "host_controller.h"
#include "widgets/select_launcher.h"

HostController::HostController(UtilCollection* u_collection): utils(u_collection){}

void HostController::run_job(QString command){
    SelectLauncher* main = new SelectLauncher();
    main->populate_command_options(utils);

    if(command != NULL && command == ""){
        // select the specified command

        if(utils->has_command(command)){
            // command is recognized
            // disable command selection
        }else{
            qWarning() << "Command not recognized: " << command.toStdString().c_str();
        }
    }else{

    }

    // open the main window
    main->showNormal();

/*
    // Time consumer
    MyTask *mytask = new MyTask();
    mytask->setAutoDelete(true);

    // using queued connection
    connect(mytask, SIGNAL(Result(int)), this, SLOT(TaskResult(int)), Qt::QueuedConnection);

    qDebug() << "Starting a new task using a thread from the QThreadPool";

    // QThreadPool::globalInstance() returns global QThreadPool instance
    QThreadPool::globalInstance()->start(mytask);
*/
    return;
}

void HostController::exec_plugin(QString command){
    if(command == NULL || command == ""){
        return;
    }

    // select the specified command

    if(utils->has_command(command)){
        // command is recognized
        // disable command selection
    }else{
        qWarning() << "Command not recognized: " << command.toStdString().c_str();
    }



    QObject* plugin = utils->util(command);
    UtilInterface *iUtil = qobject_cast<UtilInterface *>(plugin);
    if(!iUtil){return;}
    // plugin found

    iUtil->run_util();
}
