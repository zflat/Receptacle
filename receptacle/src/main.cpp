#include "QsLog.h"
#include "QsLogDest.h"

#include <QDir>
#include <iostream>
#include <QApplication>
#include "dispatcher.h"
#include "log_emitter.h"

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



QPointer<LogEmitter> logger;
void log_handler_forwarder(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    if(logger){
        logger->publish_message(type, context, msg);
    }
    //printf("%s %s %s\n", context.file, context.function, context.line);
    printf("%s\n", msg.toStdString().c_str());
}

int main(int argc, char *argv[])
{
    Console();
    logger  = new LogEmitter();
    qInstallMessageHandler(log_handler_forwarder);

    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);

    if(false){
        // init the logging mechanism
        QsLogging::Logger& logger = QsLogging::Logger::instance();
        logger.setLoggingLevel(QsLogging::TraceLevel);
        QsLogging::DestinationPtr debugDestination(\
              QsLogging::DestinationFactory::MakeDebugOutputDestination() );
        logger.addDestination(debugDestination);

        QLOG_INFO()<< "Using QsLog library";
    }

    UtilCollection* utils = new UtilCollection();
    HostController* controller = new HostController(utils, logger);

    // Create an instance of a server and then start it.
    Dispatcher server(controller);
    server.startServer();
    return app.exec();
}
