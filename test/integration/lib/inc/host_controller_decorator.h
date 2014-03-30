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


#ifndef HOST_CONTROLLER_DECORATOR_H
#define HOST_CONTROLLER_DECORATOR_H

#include <QString>
#include <QtTest>


#include "host_controller.h"

/**
 * @brief Subclass HostControllerDecorator to provide getters to protected members.
 */
class HostControllerDecorator : public HostController
{
public:
    HostControllerDecorator(UtilCollection* u_collection, LogEmitter* log_emitter): \
        HostController(u_collection, log_emitter){}
    SelectLauncher* get_main_window(){return main_window;}
    UtilInterface* get_current_util(){return current_util;}
    UtilRunner* get_bg_worker(){return bg_worker;}
};


#endif // HOST_CONTROLLER_DECORATOR_H
