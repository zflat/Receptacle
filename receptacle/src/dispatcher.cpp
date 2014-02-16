// dispatcher.cpp

#include "dispatcher.h"

Dispatcher::Dispatcher(QObject *parent) :
    QTcpServer(parent)
{
}

void Dispatcher::startServer()
{
    if(listen(QHostAddress::Any, 3333))
    {
        qDebug() << "Server: started";
    }
    else
    {
        qDebug() << "Server: not started!";
    }
}

void Dispatcher::incomingConnection(qintptr socketDescriptor)
{
    // At the incoming connection, make a client
    // and set the socket
    ClientConnection *client = new ClientConnection(this);
    client->setSocket(socketDescriptor);
}
