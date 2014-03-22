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
