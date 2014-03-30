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

#include "widgets/job_selection_form.h"

JobSelectionForm::JobSelectionForm(QWidget *parent) : QWidget(parent){
    this->btn = new QPushButton(tr("Run"));
    this->label = new QLabel(tr("Job"));
    this->box = new QComboBox(this);

    this->layout = new QHBoxLayout();
    this->layout->addWidget(this->label);
    this->layout->addWidget(this->box);
    this->layout->addWidget(this->btn);
    this->setLayout(this->layout);

    QObject::connect(this->btn, SIGNAL(pressed()), this, SLOT(btn_pressed_handler()));
}

bool JobSelectionForm::populate_command_options(UtilCollection* utils_arg){
    if(this->box->count()>0){
        return false;
    }
    QStringList commands = utils_arg->command_list();
    foreach(QString cmd, commands){
        this->box->addItem(cmd);
    }
    this->utils = utils_arg;
    return true;
}

bool JobSelectionForm::command(QString cmd){
    if(this->utils == NULL){
        // error condition
        return false;
    }

    if(cmd == NULL || cmd == ""){
        qDebug()<< tr("No command specified.");
        command_unspecified();
        return false;
    }

    if(!this->utils->has_command(cmd)){
        qDebug()<< tr("Command not recognized.");
        command_unrecognized(cmd);
        return false;
    }

    command_selected(cmd);
    this->box->setCurrentText(cmd);
    this->btn->setEnabled(false);
    this->box->setEnabled(false);
    return true;
}

void JobSelectionForm::btn_pressed_handler(){
    this->command(this->box->currentText());
    return;
}

void JobSelectionForm::indicate_msg_level(QtMsgType type){
    QString style_markup;
    switch(type){
        case QtDebugMsg:
            break;
        case QtWarningMsg:
            style_markup = "QComboBox {border: 2px solid yellow}";
            break;
        case QtCriticalMsg:
        case QtFatalMsg:
            style_markup = "QComboBox {border: 2px solid red}";
            break;
    }
    this->box->setStyleSheet(style_markup);
    qDebug() << box->styleSheet();
}
