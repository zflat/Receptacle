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


#include "widgets/select_launcher.h"

SelectLauncher::SelectLauncher(QWidget *parent) : QMainWindow(parent){
    this->setWindowTitle("Launcher");

    this->create_actions();
    this->create_menus();

    qDebug() << tr("Setup launcher started");
    QVBoxLayout* job_ui_layout = new QVBoxLayout();
    this->central_widget = new QWidget(this);
    this->tabs_widget = new QTabWidget(this->central_widget);


    this->msg_log = new LogText(this->tabs_widget);
    this->tabs_widget->addTab(this->msg_log,tr("Main"));
    this->msg_log->showMaximized();

    this->err_log = new LogText(this->tabs_widget);
    this->tabs_widget->addTab(this->err_log,tr("Error/Warn"));
    this->err_log->showMaximized();

    this->job_ui = new QWidget(this->central_widget);
    this->job_ui->setLayout(job_ui_layout);

    QVBoxLayout* central_layout= new QVBoxLayout;

    this->select_form = new JobSelectionForm(this->central_widget);
    QObject::connect(this->select_form, SIGNAL(command_selected(QString)), this, SLOT(command_selected(QString)));
    QObject::connect(this->select_form, SIGNAL(command_unrecognized(QString)), this, SLOT(command_rejected(QString)));
    QObject::connect(this->select_form, SIGNAL(command_unspecified()), this, SLOT(command_pending()));

    central_layout->addWidget(this->select_form);
    //central_layout->addWidget(this->job_ui);
    central_layout->addWidget(this->tabs_widget);

    this->central_widget->setLayout(central_layout);
    this->setCentralWidget(this->central_widget);
}


void SelectLauncher::create_menus(){

    menu_file = menuBar()->addMenu(tr("&File"));
    menu_file->addAction(exitAct);

    menu_file->addAction(saveLogText);
    menu_file->addAction(saveErrWarnText);
}

void SelectLauncher::create_actions(){
    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));


    saveLogText = new QAction(tr("Save Log"), this);
    connect(saveLogText, SIGNAL(triggered()), this, SLOT(save_log_text()));
    saveErrWarnText = new QAction(tr("Save errors & warnings log"), this);
    connect(saveErrWarnText, SIGNAL(triggered()), this, SLOT(save_err_warn_text()));

}


bool SelectLauncher::connect_logger(LogEmitter* log_emitter){
    if(!log_emitter || !this->msg_log || !this->err_log)
        return false;

    this->logger = log_emitter;
    QObject::connect(this->logger, &LogEmitter::info_message,\
                     this->msg_log, &LogText::appendText);
    QObject::connect(this->logger, &LogEmitter::warn_message,\
                     this->msg_log, &LogText::appendText);
    QObject::connect(this->logger, &LogEmitter::critical_message,\
                     this->msg_log, &LogText::appendText);
    QObject::connect(this->logger, &LogEmitter::fatal_message,\
                     this->msg_log, &LogText::appendText);


    QObject::connect(this->logger, &LogEmitter::warn_message,\
                     this->err_log, &LogText::appendText);
    QObject::connect(this->logger, &LogEmitter::critical_message,\
                     this->err_log, &LogText::appendText);
    QObject::connect(this->logger, &LogEmitter::fatal_message,\
                     this->err_log, &LogText::appendText);

    return true;
}

void SelectLauncher::command_selected(QString cmd){
    selected(cmd);
}

void SelectLauncher::command_rejected(QString cmd){

}

void SelectLauncher::command_pending(){

}

void SelectLauncher::select_job(QString cmd){
    this->select_form->command(cmd);
}

bool SelectLauncher::populate_command_options(UtilCollection* utils){
    return this->select_form->populate_command_options(utils);
}

bool SelectLauncher::load_job_widget(QWidget *job_ui_widget){
    return false;
}


void SelectLauncher::closeEvent(QCloseEvent *event){
   emit close_sig();
   event->accept();
}


void SelectLauncher::save_log_text(){
    QString saveFileName = QFileDialog::getSaveFileName(
                  this,
                  tr("Save Log Output"),
                  tr("%1/logfile.txt").arg(QDir::homePath()),
                  tr("Text Files (*.txt);;All Files (*)")
                  );

    if(saveFileName.isEmpty())
        return;

    this->msg_log->save_to_file(saveFileName);
}

void SelectLauncher::save_err_warn_text(){
    QString saveFileName = QFileDialog::getSaveFileName(
                  this,
                  tr("Save Log Output"),
                  tr("%1/err_warn_file.txt").arg(QDir::homePath()),
                  tr("Text Files (*.txt);;All Files (*)")
                  );

    if(saveFileName.isEmpty())
        return;

    this->err_log->save_to_file(saveFileName);
}