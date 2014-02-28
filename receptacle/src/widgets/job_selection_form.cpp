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

bool JobSelectionForm::populate_command_options(UtilCollection* utils){
    if(this->box->count()>0){
        return false;
    }

    QStringList commands = utils->command_list();
    foreach(QString cmd, commands){
        this->box->addItem(cmd);
    }
    return true;
}

bool JobSelectionForm::select_job(QString cmd){
    this->box->setCurrentText(cmd);
    this->btn->setEnabled(false);
    this->box->setEnabled(false);
}
