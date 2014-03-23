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

#ifndef SELECT_LAUNCHER_H
#define SELECT_LAUNCHER_H

#include <QtWidgets/QMainWindow>
#include <QWidget>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QDir>
#include "util_collection.h"
#include "job_selection_form.h"
#include "log_text.h"
#include "log_emitter.h"

class SelectLauncher : public QMainWindow{
    Q_OBJECT

public:
    SelectLauncher(QWidget *parent=0);
    bool populate_command_options(UtilCollection* utils);
    bool connect_logger(LogEmitter* log_emitter);
    void select_job(QString command);
    bool load_job_widget(QWidget* job_ui_widget);

protected slots:
    void command_selected(QString cmd);
    void command_rejected(QString cmd);
    void command_pending();

signals:
    void close_sig();
    void selected(QString cmd);

protected:
    //menubar
    QMenuBar* menubar;
    //menufile
    QMenu* menu_file;
    //menuhelp
    QMenu* menu_help;

    //menu actions

    //status bar

    //central widget and layout
    QWidget* central_widget;

    //job selection form
    JobSelectionForm* select_form;

    QWidget* job_ui;
    //job ui layout
    //QVBoxLayout* job_ui_layout;

    //tabs
    QTabWidget* tabs_widget;

    //log text page
    LogText* msg_log;

    //err/warn text page
    LogText* err_log;

    LogEmitter* logger;

    QAction* exitAct;
    QAction* saveLogText;
    QAction* saveErrWarnText;
    QAction* aboutAct;
    QAction* aboutQtAct;
    QAction* aboutPluginsAct;

protected:
    void create_menus();
    void create_actions();
    void closeEvent(QCloseEvent *event);

protected slots:
    void save_log_text();
    void save_err_warn_text();
};

#endif // SELECT_LAUNCHER_H
