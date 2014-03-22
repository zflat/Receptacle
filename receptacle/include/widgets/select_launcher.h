#ifndef SELECT_LAUNCHER_H
#define SELECT_LAUNCHER_H

#include <QtWidgets/QMainWindow>
#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
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
    //menufile
    //menuhelp

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

protected:
     void closeEvent(QCloseEvent *event);
};

#endif // SELECT_LAUNCHER_H
