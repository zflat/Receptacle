#ifndef SELECT_LAUNCHER_H
#define SELECT_LAUNCHER_H

#include <QtWidgets/QMainWindow>
#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include "util_collection.h"
#include "job_selection_form.h"

class SelectLauncher : public QMainWindow{
    Q_OBJECT

public:
    SelectLauncher(QWidget *parent=0);
    bool populate_command_options(UtilCollection* utils);
    bool select_job(QString command);

signals:
    void close_sig();
    void command_selected(QString);

private:
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
    //err/warn text page


};

#endif // SELECT_LAUNCHER_H
