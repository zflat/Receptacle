// dispatcher.h

#ifndef DISPATCHER_H
#define DISPATCHER_H

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

signals:

public slots:

};

#endif // DISPATCHER_H
