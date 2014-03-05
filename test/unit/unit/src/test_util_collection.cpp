#include "util_collection.h"
#include "test_util_collection.h"


void TestUtilCollection::constructor(){
    // CASE: without specifying a utils directory


    // CASE: when specifying a utils directory

}

void TestUtilCollection::has_command(){
    // CASE: command that is not part of the collection
    UtilCollection* utils = new UtilCollection();    
    QCOMPARE(utils->has_command("test_command"), false);

    // CASE: null command
    utils = new UtilCollection();
    QCOMPARE(utils->has_command(NULL), false);

    // CASE: command that is part of the collection

}

void TestUtilCollection::insert_util(){
    // CASE: Adding NULL
    UtilCollection* utils = new UtilCollection();
    QCOMPARE(utils->insert_util(NULL), false);

    // CASE: Adding uninitialized QObject
    utils = new UtilCollection();
    QObject* obj;
    QCOMPARE(utils->insert_util(obj), false);

    // CASE: Adding a non-util object
    utils = new UtilCollection();
    obj= new QObject();
    QCOMPARE(utils->insert_util(obj), false);

    // CASE: Adding a util object

}

void TestUtilCollection::command_list(){
    // CASE: where there are no utils loaded
    UtilCollection* utils = new UtilCollection();
    QCOMPARE(utils->command_list().empty(), true);

    // CASE: where there are utils loaded

}
