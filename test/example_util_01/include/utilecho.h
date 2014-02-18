#include <QObject>
#include <QString>

#include "util_interface.h"

class UtilEcho : public QObject, public UtilInterface
{
    Q_OBJECT    
    Q_PLUGIN_METADATA(IID "Receptacle.plugins.UtilInterface-v0.0.1")
    Q_INTERFACES(UtilInterface)

public:
    QString name() const;
    void run_util();
};
