// dispatcher.h

#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QDir>
#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QSemaphore>


#include "host_controller.h"
#include "client_connection.h"

class Dispatcher : public QTcpServer
{
    Q_OBJECT
public:
    ~Dispatcher();
    explicit Dispatcher(HostController* h_controller, QObject *parent = 0);
    void startServer();
    bool queue_busy();

 protected:
    void incomingConnection(qintptr socketDescriptor);

 protected:
    HostController* controller;
    QSemaphore request_mutex;

public slots:
    void queue_request(QString command);
    void request_completed(QString command);

};

#endif // DISPATCHER_H
