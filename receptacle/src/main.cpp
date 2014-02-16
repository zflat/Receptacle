#include <QCoreApplication>
#include "dispatcher.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Create an instance of a server and then start it.
    Dispatcher server;
    server.startServer();

    return a.exec();
}
