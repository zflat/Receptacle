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
        qDebug()<< "No command specified.";
        command_unspecified();
        return false;
    }

    if(!this->utils->has_command(cmd)){
        qDebug()<< "Command not recognized.";
        command_unrecognized(cmd);
        return false;
    }

    command_selected(cmd);
    this->box->setCurrentText(cmd);
    this->btn->setEnabled(false);
    this->box->setEnabled(false);
    return true;
}
