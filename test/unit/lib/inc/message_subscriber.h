#ifndef MESSAGE_SUBSCRIBER_H
#define MESSAGE_SUBSCRIBER_H

#include <QObject>

class MessageSubscriber : public QObject
{
    Q_OBJECT
public:
    explicit MessageSubscriber(QObject *parent = 0);
    QString* getMessage();

signals:

public slots:
    void set_message(const QString &msg);
private:
    QString message;
};

#endif // MESSAGE_SUBSCRIBER_H
