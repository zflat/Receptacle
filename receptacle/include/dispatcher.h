// dispatcher.h

#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QDir>
#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include "client_connection.h"

class Dispatcher : public QTcpServer
{
    Q_OBJECT
public:
    explicit Dispatcher(QObject *parent = 0);
    void startServer();

 protected:
    void incomingConnection(qintptr socketDescriptor);

 private:
    QDir pluginsDir;
    void loadPlugins();
    void populatePlugin(QObject *plugin);

signals:

public slots:

};

#endif // DISPATCHER_H
