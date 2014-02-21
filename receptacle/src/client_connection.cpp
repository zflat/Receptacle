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

    qDebug() << "A new socket created!";

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    socket->setSocketDescriptor(descriptor);

    qDebug() << " Client connected at " << descriptor;
}


// asynchronous - runs separately from the thread we created
void ClientConnection::connected()
{
    qDebug() << "Client connected event";
}

// asynchronous
void ClientConnection::disconnected()
{
    qDebug() << "Client disconnected";
}

// Our main thread of execution
// This happening via main thread
// Our code running in our current thread not in another QThread
// That's why we're getting the thread from the pool

void ClientConnection::readyRead()
{
    qDebug() << "ClientConnection::readyRead()";
    //qDebug() << socket->readAll();
    QString command = socket->readLine();
    emit command_sent(command);

    // Time consumer
    MyTask *mytask = new MyTask();
    mytask->setAutoDelete(true);
    
    // using queued connection
    connect(mytask, SIGNAL(Result(int)), this, SLOT(TaskResult(int)), Qt::QueuedConnection);

    qDebug() << "Starting a new task using a thread from the QThreadPool";
    
    // QThreadPool::globalInstance() returns global QThreadPool instance
    QThreadPool::globalInstance()->start(mytask);

}

// After a task performed a time consuming task,
// we grab the result here, and send it to client
void ClientConnection::TaskResult(int Number)
{
    QByteArray Buffer;
    Buffer.append("\r\nTask result = ");
    Buffer.append(QString::number(Number));

    socket->write(Buffer);
}
