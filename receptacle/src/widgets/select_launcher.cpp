#include "widgets/select_launcher.h"

SelectLauncher::SelectLauncher(QWidget *parent) : QMainWindow(parent){

    qDebug() << "Setup launcher started";
    QVBoxLayout* job_ui_layout = new QVBoxLayout;

    this->central_widget = new QWidget(this);
    this->tabs_widget = new QTabWidget(this->central_widget);

    this->job_ui = new QWidget(this->central_widget);
    this->job_ui->setLayout(job_ui_layout);

    QVBoxLayout* central_layout= new QVBoxLayout;

    this->select_form = new JobSelectionForm(this->central_widget);
    central_layout->addWidget(this->select_form);
    //central_layout->addWidget(this->job_ui);
    //central_layout->addWidget(this->tabs_widget);

    this->central_widget->setLayout(central_layout);
    this->setCentralWidget(this->central_widget);
}

bool SelectLauncher::select_job(QString command){

}

bool SelectLauncher::populate_command_options(UtilCollection* utils){
    return this->select_form->populate_command_options(utils);
}
