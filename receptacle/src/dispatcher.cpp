// dispatcher.cpp

#include "dispatcher.h"
#include "util_interface.h"

Dispatcher::Dispatcher(QObject *parent) : QTcpServer(parent), utils(){}

void Dispatcher::startServer()
{
  if(listen(QHostAddress::Any, 3333)){
    qDebug() << "Server: started";
  }
  else{
    qDebug() << "Server: not started!";
  }
}

void Dispatcher::incomingConnection(qintptr socketDescriptor)
{
    // At the incoming connection, make a client
    // and set the socket
    ClientConnection *client = new ClientConnection(this);
    client->setSocket(socketDescriptor);

    // subscribe to command_sent signal
    connect(client, SIGNAL(command_sent(QString)), this, SLOT(queue_request(QString)));
}


void Dispatcher::queue_request(QString command){
    qDebug() << "Requested command queued: " << command.toStdString().c_str();
    return;
}
