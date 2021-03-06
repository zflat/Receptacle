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

#include <QApplication>

#include "dispatcher.h"
#include "util_interface.h"

Dispatcher::Dispatcher(HostController* h_controller, QObject *parent)\
    : QTcpServer(parent), controller(h_controller), request_mutex(1){
    QObject::connect(controller, SIGNAL(end_job(const QString &)), this, SLOT(request_completed(const QString &)));
}

Dispatcher::~Dispatcher(){
    this->close();
    request_mutex.release(request_mutex.available());

    if( qApp->property("optn.verbose").toBool()){
        qDebug()<<"Server closed";
    }
}

void Dispatcher::startServer(int port)
{
  bool is_listening = listen(QHostAddress::Any, port);

  if(is_listening){
    qDebug() << tr("Dispatcher: listening on port").toStdString().c_str() << port;
  }
  else{
    qWarning() << tr("Dispatcher: not started!");
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
    command = command.trimmed();
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
   if( qApp->property("optn.verbose").toBool()){
    qDebug() << "check for busy server";
   }
   return this->request_mutex.available()<1;
}

void Dispatcher::request_completed(const QString &command){
    this->request_mutex.release(1);

    if( qApp->property("optn.verbose").toBool()){
        qDebug() << "Request " \
                 << command.toStdString().c_str() <<" ended.";
        qDebug() << "request_mutex released";
    }
}
