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
#include <QHash>
#include "util_collection.h"
#include "job_selection_form.h"
#include "log_text.h"
#include "log_emitter.h"
#include "signal_counter.h"

class SelectLauncher : public QMainWindow{
    Q_OBJECT

public:
    SelectLauncher();
    bool populate_command_options(UtilCollection* utils);
    bool connect_logger(LogEmitter* log_emitter);
    bool connect_errwarn_flag(SignalCounter* err_flag, SignalCounter* fatal_flag, SignalCounter* warn_flag);

    /**
     * @brief attach_widget adds the given widget to the host GUI
     * @param w
     *   QWidget parent widget for the plugin UI
     * @param type
     *   QString either "simple" or "complex"
     * @return
     *   True on success, False otherwise
     */
    bool attach_widget(QWidget* w, const QString &type);

    void select_job(QString command);
    bool load_job_widget(QWidget* job_ui_widget);
    bool set_is_running_bg(bool is_running);
    bool get_is_pending_close();

signals:
    /**
     * @brief close_requested broadcasts when a close event is
     * requested but ignored because a bg worker is still runing.
     */
    void close_requested();

    void selected(QString cmd);

public slots:

    /**
     * @brief Visual indication that the message type has been published
     * @param type
     *   QtMsgType indicating the error level
     * @param is_notification
     *   bool indicating if this is an indidication (less obtrusive) or notification (more obtrusive)
     */
    void show_msg_level(QtMsgType type, bool is_notification);

   // void show_warning(QString str);
   // void show_err(QString str);

protected slots:
    void command_selected(QString cmd);
    void command_rejected(QString cmd);
    void command_pending();
    void save_log_text();
    void save_err_warn_text();

    void indicate_error();
    void indicate_warning();

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
    QVBoxLayout* central_layout;

    //job selection form
    JobSelectionForm* select_form;

    // Plugin UI widget
    QWidget* plugin_widget;

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

    /**
     * @brief is_running_bg True when a background worker is running
     */
    bool is_running_bg;

    /**
     * @brief pending_close indicates a close event has been sent but not yet accepted
     */
    bool is_pending_close;

    SignalCounter* err_flag;
    SignalCounter* warn_flag;
    SignalCounter* fatal_flag;

protected:
    void create_menus();
    void create_actions();
    void closeEvent(QCloseEvent *event);

};

#endif // SELECT_LAUNCHER_H
