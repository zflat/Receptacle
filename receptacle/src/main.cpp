#include "QsLog.h"
#include "QsLogDest.h"

#include <QDir>
#include <iostream>
#include <QCoreApplication>
#include "dispatcher.h"

/*
 * Console output with GUI in windows
 * http://stackoverflow.com/a/20733453
 */
void Console()
{
#if defined(Q_OS_WIN)
    AllocConsole();
    FILE *pFileCon = NULL;
    pFileCon = freopen("CONOUT$", "w", stdout);

    COORD coordInfo;
    coordInfo.X = 130;
    coordInfo.Y = 9000;

    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coordInfo);
    SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE),ENABLE_QUICK_EDIT_MODE| ENABLE_EXTENDED_FLAGS);
#endif
}

int main(int argc, char *argv[])
{
    Console();

    QCoreApplication app(argc, argv);

    // init the logging mechanism
    QsLogging::Logger& logger = QsLogging::Logger::instance();
    logger.setLoggingLevel(QsLogging::TraceLevel);
    QsLogging::DestinationPtr debugDestination(\
          QsLogging::DestinationFactory::MakeDebugOutputDestination() );
    logger.addDestination(debugDestination);

    QLOG_INFO()<< "Using QsLog library";

    UtilCollection* utils = new UtilCollection();
    HostController* controller = new HostController(utils);

    // Create an instance of a server and then start it.
    Dispatcher server(controller);
    server.startServer();
    return app.exec();
}
