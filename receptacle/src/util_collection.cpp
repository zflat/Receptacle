#include "util_collection.h"

UtilCollection::UtilCollection() : util_hash(){
}

UtilCollection::~UtilCollection(){
    delete &util_hash;
}

QHashIterator<QString, QObject*> UtilCollection::plugins(){
    return (QHashIterator<QString, QObject*>(util_hash));
}


QStringList UtilCollection::command_list(){
    new QStringList(this->util_hash.keys());
}


QObject* UtilCollection::util(QString command){
    return NULL;
}


bool UtilCollection::insert_util(QObject *util_obj){
    UtilInterface *iUtil = qobject_cast<UtilInterface *>(util_obj);
    if(iUtil){
        util_hash.insert(iUtil->command(), util_obj);
        return true;
    }else{return false;}
}


bool UtilCollection::is_command(QString commmand){
    return false;
}
