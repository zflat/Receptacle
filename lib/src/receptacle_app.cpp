#include "receptacle_app.h"

ReceptacleApp::ReceptacleApp(int &argc, char **argv): QApplication(argc, argv), \
    server(NULL), utils(NULL), controller(NULL){}

ReceptacleApp::~ReceptacleApp(){
    // TODO catch ctrl+c
    // http://stackoverflow.com/questions/7581343/how-to-catch-ctrlc-on-windows-and-linux-with-qt

    delete controller;
    controller = NULL;
    delete utils;
    utils = NULL;
    delete server;
    server = NULL;

    if( qApp->property("optn.verbose").toBool()){
        qDebug() << "Application cleanup complete";
    }
}


void ReceptacleApp::startServer(int port, LogEmitter * logger){
    // Check that the server is not already running

    if(NULL != server){
        qWarning() << "Server is already running";
        return;
    }

    utils = new UtilCollection();
    controller = new HostController(utils, logger);

    // Create an instance of a server and then start it.
    server = new Dispatcher(controller);
    server->startServer(port);
}
