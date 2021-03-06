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

#include <QDir>
#include <iostream>
#include <QApplication>
#include <QCommandLineParser>
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

    if( qApp->property("optn.console").toBool()){
        printf("%s\n", msg.toStdString().c_str());
    }
}

int main(int argc, char *argv[])
{    
    qsrand(QTime::currentTime().msec());

    QApplication app(argc, argv);
    QApplication::setApplicationName("Receptacle");
    QApplication::setApplicationVersion(APP_VERSION);
    app.setQuitOnLastWindowClosed(false);

    QCommandLineParser cmd_args;
    cmd_args.addHelpOption();
    cmd_args.addVersionOption();
    QCommandLineOption consoleOut(QStringList() << "c" << "console", \
                                  QApplication::translate("main", "Print stdout to console"));
    cmd_args.addOption(consoleOut);
    QCommandLineOption listenPort(QStringList() << "p" << "port", \
                                  QApplication::translate("main", "Dispatcher listens on <port>"), \
                                  QApplication::translate("main", "port"));
    cmd_args.addOption(listenPort);
    QCommandLineOption verboseLogging(QStringList() << "verbose", \
                                  QApplication::translate("main", "Verbose logging"));
    cmd_args.addOption(verboseLogging);
    cmd_args.process(app);

    if(cmd_args.isSet("verbose")){
        app.setProperty("optn.verbose", QVariant(true));
    }

    if(cmd_args.isSet("console")){
        app.setProperty("optn.console", QVariant(true));
        Console();
    }
    logger  = new LogEmitter();
    qInstallMessageHandler(log_handler_forwarder);


    if( qApp->property("optn.verbose").toBool()){
        qDebug() << qApp->applicationVersion();
        qDebug() << qApp->applicationDirPath();
    }


    UtilCollection* utils = new UtilCollection();
    HostController* controller = new HostController(utils, logger);

    // Create an instance of a server and then start it.
    Dispatcher server(controller);

    QFile settingsFile(qApp->applicationDirPath() + QDir::separator() + "config.json");
    if (!settingsFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open application settings JSON file.");
        exit(-1);
    }

    QByteArray settingsData = settingsFile.readAll();
    QJsonDocument settingsDoc(QJsonDocument::fromJson(settingsData));
    QVariantMap settignsMap = qvariant_cast<QVariantMap>(settingsDoc.toVariant());

    bool port_setting_read;
    int port_setting = settignsMap.value("port").toInt(&port_setting_read);
    QStringList plugins_ordered_list = \
            qvariant_cast<QVariant>(settignsMap.value("plugin_order")).toStringList();
    foreach(QString plugin_cmd, plugins_ordered_list){
        if( qApp->property("optn.verbose").toBool()){
            qDebug() << plugin_cmd;
        }
    }


    bool port_parsed;
    int dec_port = cmd_args.value("port").toInt(&port_parsed);

    if(port_parsed){        
        if( qApp->property("optn.verbose").toBool()){
            qDebug() << dec_port;
        }
        server.startServer(dec_port);
        return app.exec();
    }else if(port_setting_read){
        server.startServer(port_setting);
        return app.exec();
    }else{
        return(0);
    }

}
