// client_connection.h

#ifndef CLIENT_CONNECION_H
#define CLIENT_CONNECTION_H

#include <QObject>
#include <QTcpSocket>
#include <QThreadPool>
#include <QDebug>

class ClientConnection : public QObject
{
    Q_OBJECT
public:
    explicit ClientConnection(QObject *parent = 0);
    void setSocket(qintptr descriptor);

signals:
    void command_sent(QString commmand);

public slots:
    void connected();
    void disconnected();
    void readyRead();

    // make the server fully ascynchronous
    // by doing time consuming task
    void TaskResult(int Number);

private:
    QTcpSocket *socket;

};

#endif // CLIENT_CONNECTION_H
