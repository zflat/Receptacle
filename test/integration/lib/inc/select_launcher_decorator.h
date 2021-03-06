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


#ifndef SELECT_LAUNCHER_DECORATOR_H
#define SELECT_LAUNCHER_DECORATOR_H

#include <QString>
#include <QtTest>

#include "widgets/select_launcher.h"
#include "job_selection_form_decorator.h"

/**
 * @brief Subclass HostControllerDecorator to provide getters to protected members.
 */
class SelectLauncherDecorator : public SelectLauncher
{
public:
    SelectLauncherDecorator() : SelectLauncher(){
    }

    JobSelectionFormDecorator* get_job_select_form(){
        return static_cast<JobSelectionFormDecorator*>(select_form);
    }

    QWidget* get_plugin_widget(){
        return this->plugin_widget;
    }

    QAction* getExitMenuAction(){
        return this->exitAct;
    }

    QWidget* get_menu_file(){
        return this->menu_file;
    }

};


#endif // SELECT_LAUNCHER_DECORATOR_H
