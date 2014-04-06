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

    /**
     * @brief Call startServer to listen for client connections. Server does not process requests until this is called.
     */
    void startServer();

    /**
     * @brief A 'busy signal' check.
     * @return True when the dispatcher is busy, false otherwise
     */
    bool queue_busy();

 protected:
    void incomingConnection(qintptr socketDescriptor);

 protected:
    HostController* controller;
    QSemaphore request_mutex;

public slots:
    /**
     * @brief Asynchronous request for a job to run
     * @param QString command specifying the requested job
     */
    void queue_request(QString command);

    /**
     * @brief Handler to cleanup after a job finishes and prepares for the next job to run.
     * @param QString command of the job that just finished
     */
    void request_completed(const QString &command);

};

#endif // DISPATCHER_H
