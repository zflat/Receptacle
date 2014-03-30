/*

Copyright 2014 William Wedler

This file is part of Receptacle

Receptacle is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Receptacle is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Receptacle.  If not, see <http://www.gnu.org/licenses/>.

*/

// dispatcher.cpp

#include "dispatcher.h"
#include "util_interface.h"

Dispatcher::Dispatcher(HostController* h_controller, QObject *parent)\
    : QTcpServer(parent), controller(h_controller), request_mutex(1){
    QObject::connect(controller, SIGNAL(end_job(QString)), this, SLOT(request_completed(QString)));
}

Dispatcher::~Dispatcher(){
    this->close();
    request_mutex.release(request_mutex.available());
    qDebug()<<"Server closed";
}

void Dispatcher::startServer()
{
  if(listen(QHostAddress::Any, 3333)){
    qDebug() << tr("Server: started");
  }
  else{
    qDebug() << tr("Server: not started!");
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
    if(this->request_mutex.tryAcquire(1, 100)){
        qDebug() << "Requested command queued: " << command.toStdString().c_str();
        controller->run_job(command);
    }else{
        qDebug() << "Requested command" \
                 << command.toStdString().c_str() <<" blocked.";
    }
    return;
}

bool Dispatcher::queue_busy(){
   qDebug() << "check for busy server";
   return this->request_mutex.available()<1;
}

void Dispatcher::request_completed(QString command){
    qDebug() << "Request " \
             << command.toStdString().c_str() <<" ended.";
    this->request_mutex.release(1);
    qDebug() << "request_mutex released";
}
