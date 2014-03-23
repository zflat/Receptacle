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

    // CASE: Adding NULL pointer
    utils = new UtilCollection();
    QObject* obj=NULL;
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
