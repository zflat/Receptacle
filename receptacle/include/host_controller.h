#ifndef HOST_CONTROLLER_H
#define HOST_CONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QThreadPool>
#include "mytask.h"
#include "util_collection.h"

class HostController : public QObject
{
    Q_OBJECT
public:
    HostController(UtilCollection* u_collection);
    void run_job(QString command);

private:
    UtilCollection* utils;

private slots:
       void exec_plugin(QString command);
};

#endif // HOST_CONTROLLER_H
