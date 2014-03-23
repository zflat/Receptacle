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


#ifndef UTIL_COLLECTION_H
#define UTIL_COLLECTION_H


#include <QDir>
#include <QHash>
#include <QString>
#include <QStringList>

#include "util_interface.h"

class UtilCollection{
public:
    UtilCollection();
    ~UtilCollection();

    /*
     * All plugins loaded as utils in the collection
     */
    QHashIterator<QString, QObject*> plugins();

    /*
     * List of commands for each util
     */
    QStringList command_list();

    /*
     * Plugin corresponding to the give command
     */
    QObject* util(QString command);

    /*
     * Add a plugin as a util to the collection
     */
    bool insert_util(QObject *util_obj);

    /*
     * Test if the given command is recognized in the command list
     */
    bool has_command(QString commmand);

protected:
    QDir pluginsDir;
    void loadPlugins();
    void populateUtil(QObject *plugin);

    QHash<QString, QObject*> util_hash;
};

#endif // UTIL_COLLECTION_H
