// dispatcher.h

#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QDir>
#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QMutex>


#include "host_controller.h"
#include "client_connection.h"

class Dispatcher : public QTcpServer
{
    Q_OBJECT
public:
    explicit Dispatcher(HostController* h_controller, QObject *parent = 0);
    void startServer();

 protected:
    void incomingConnection(qintptr socketDescriptor);

 private:
    QMutex request_mutex;
    HostController* controller;

signals:

public slots:
    void queue_request(QString command);

};

#endif // DISPATCHER_H
