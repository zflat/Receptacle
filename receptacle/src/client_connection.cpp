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


// client_connection.cpp

#include "client_connection.h"

ClientConnection::ClientConnection(QObject *parent) :
    QObject(parent)
{
    QThreadPool::globalInstance()->setMaxThreadCount(5);
}

void ClientConnection::setSocket(qintptr descriptor)
{
    // make a new socket
    socket = new QTcpSocket(this);

    qDebug() << tr("A new socket created!");

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    socket->setSocketDescriptor(descriptor);

    qDebug() << tr(" Client connected at ") << descriptor;
}


// asynchronous - runs separately from the thread we created
void ClientConnection::connected()
{
    qDebug() << tr("Client connected event");
}

// asynchronous
void ClientConnection::disconnected()
{
    qDebug() << tr("Client disconnected");
    delete this;
}

// Our main thread of execution
// This happening via main thread
// Our code running in our current thread not in another QThread
// That's why we're getting the thread from the pool

void ClientConnection::readyRead()
{
    qDebug() << tr("ClientConnection::readyRead()");
    //qDebug() << socket->readAll();
    QString command = socket->readLine();
    emit command_sent(command);

}

// After a task performed a time consuming task,
// we grab the result here, and send it to client
void ClientConnection::TaskResult(int Number)
{
    QByteArray Buffer;
    Buffer.append(tr("\r\nTask result = "));
    Buffer.append(QString::number(Number));

    socket->write(Buffer);
}
