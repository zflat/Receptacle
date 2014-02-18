// dispatcher.cpp

#include <QApplication>
#include <QPluginLoader>
#include "dispatcher.h"
#include "util_interface.h"

Dispatcher::Dispatcher(QObject *parent) : QTcpServer(parent){
  this->loadPlugins();
}

void Dispatcher::loadPlugins(){
  pluginsDir = QDir(qApp->applicationDirPath());

#if defined(Q_OS_WIN)
  if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
    pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
  if (pluginsDir.dirName() == "MacOS") {
    pluginsDir.cdUp();
    pluginsDir.cdUp();
    pluginsDir.cdUp();
  }
#endif

  pluginsDir.cd("plugins");
  foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
    QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
    QObject *plugin = loader.instance();
    if (plugin) {
      // Add plugin to the list based on fileName
      qDebug() << "Valid plugin file: " ;
      qDebug() << fileName.toStdString().c_str() << endl;
    }
  }
  
}

void Dispatcher::populatePlugin(QObject *plugin){
  UtilInterface *iUtil = qobject_cast<UtilInterface *>(plugin);
  if(iUtil){
    // the plugin implements UtilInterface
    
  }
}

void Dispatcher::startServer()
{
  if(listen(QHostAddress::Any, 3333)){
    qDebug() << "Server: started";
  }
  else{
    qDebug() << "Server: not started!";
  }
}

void Dispatcher::incomingConnection(qintptr socketDescriptor)
{
    // At the incoming connection, make a client
    // and set the socket
    ClientConnection *client = new ClientConnection(this);
    client->setSocket(socketDescriptor);
}
