#ifndef HOST_CONTROLLER_H
#define HOST_CONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QThreadPool>
#include "util_worker.h"
#include "util_collection.h"
#include "widgets/select_launcher.h"

class HostController : public QObject
{
    Q_OBJECT
public:
    HostController(UtilCollection* u_collection);
    void run_job(QString command);
    void notify_block();
signals:
    void end_job(QString cmd);

public slots:
    void selected(QString cmd);

private:
    UtilCollection* utils;
    SelectLauncher* main_window;
    UtilInterface* current_util;

private slots:
       void exec_plugin(QString command);
       void cancel_handler();
       void job_complete_handler();
};

#endif // HOST_CONTROLLER_H
