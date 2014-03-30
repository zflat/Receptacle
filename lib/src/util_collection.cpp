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

#include <QApplication>
#include <QPluginLoader>
#include <QDebug>

#include "util_collection.h"
#include "util_interface.h"

UtilCollection::UtilCollection() : util_hash(){
    this->loadPlugins();
}

UtilCollection::~UtilCollection(){}


QHashIterator<QString, QObject*> UtilCollection::plugins(){
    return (QHashIterator<QString, QObject*>(util_hash));
}


QStringList UtilCollection::command_list(){
    return (QStringList(this->util_hash.keys()));
}


QObject* UtilCollection::util(QString command){
    return util_hash[command];
}


bool UtilCollection::insert_util(QObject *util_obj){
    UtilInterface *iUtil = qobject_cast<UtilInterface *>(util_obj);
    if(iUtil){
        util_hash.insert(iUtil->command(), util_obj);
        return true;
    }else{return false;}
}

bool UtilCollection::has_command(QString commmand){
    return util_hash.keys().contains(commmand);
}

void UtilCollection::loadPlugins(){
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
      qDebug() << "Plugin found: " << fileName.toStdString().c_str();
      populateUtil(plugin);
    }
  }

}


void UtilCollection::populateUtil(QObject *plugin){
  UtilInterface *iUtil = qobject_cast<UtilInterface *>(plugin);
  if(iUtil && this->insert_util(plugin)){
    // the plugin implements UtilInterface
    qDebug() << "Added util: " << iUtil->name().toStdString().c_str();
  }
}
