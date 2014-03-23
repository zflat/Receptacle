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
