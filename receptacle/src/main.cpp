#include <QCoreApplication>
#include "dispatcher.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    UtilCollection* utils = new UtilCollection();
    HostController* controller = new HostController(utils);

    // Create an instance of a server and then start it.
    Dispatcher server(controller);
    server.startServer();

    return app.exec();
}
