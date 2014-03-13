#ifndef UTILECHO_H
#define UTILECHO_H
#include <QObject>
#include <QString>

#include "util_interface.h"
#include "util_worker_interface.h"

class UtilEcho : public QObject, public UtilInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Receptacle.plugins.UtilInterface-v0.0.1")
    Q_INTERFACES(UtilInterface)

public:
    QString name() const;
    QString description() const;
    QString command() const;
    UtilWorkerInterface* newWorker();
};
#endif