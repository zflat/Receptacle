#include "message_subscriber.h"

MessageSubscriber::MessageSubscriber(QObject *parent) :
    QObject(parent), message(QString(""))
{
}

void MessageSubscriber::set_message(const QString &msg){
    this->message = msg.trimmed();
    return;
}

QString* MessageSubscriber::getMessage(){
    return &this->message;
}
