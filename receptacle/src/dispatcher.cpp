// dispatcher.cpp

#include "dispatcher.h"
#include "util_interface.h"

Dispatcher::Dispatcher(HostController* h_controller, QObject *parent)\
    : QTcpServer(parent), controller(h_controller){
    QObject::connect(controller, SIGNAL(end_job(QString)), this, SLOT(request_completed(QString)));
}

Dispatcher::~Dispatcher(){
    this->request_mutex.unlock();
}

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
    connect(client, SIGNAL(command_sent(QString)), \
            this, SLOT(queue_request(QString)));
}


void Dispatcher::queue_request(QString command){
    if(this->request_mutex.tryLock(100)){
        qDebug() << "Requested command queued: " << command.toStdString().c_str();
        controller->run_job(command);
    }else{
        qDebug() << "Requested command" \
                 << command.toStdString().c_str() <<" blocked.";
    }
    return;
}

bool Dispatcher::queue_busy(){
   return !this->request_mutex.tryLock(10);
}

void Dispatcher::request_completed(QString command){
    qDebug() << "Request " \
             << command.toStdString().c_str() <<" ended.";
    this->request_mutex.unlock();
}
