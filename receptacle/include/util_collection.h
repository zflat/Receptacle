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
    bool is_command(QString commmand);

private:
    QDir pluginsDir;
    void loadPlugins();
    void populateUtil(QObject *plugin);

    QHash<QString, QObject*> util_hash;
};

#endif // UTIL_COLLECTION_H
