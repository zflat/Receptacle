#include "widgets/select_launcher.h"

SelectLauncher::SelectLauncher(QWidget *parent) : QMainWindow(parent){

    qDebug() << "Setup launcher started";
    QVBoxLayout* job_ui_layout = new QVBoxLayout();
    this->central_widget = new QWidget(this);
    this->tabs_widget = new QTabWidget(this->central_widget);

    this->job_ui = new QWidget(this->central_widget);
    this->job_ui->setLayout(job_ui_layout);

    QVBoxLayout* central_layout= new QVBoxLayout;

    this->select_form = new JobSelectionForm(this->central_widget);
    QObject::connect(this->select_form, SIGNAL(command_selected(QString)), this, SLOT(command_selected(QString)));
    QObject::connect(this->select_form, SIGNAL(command_unrecognized(QString)), this, SLOT(command_rejected(QString)));
    QObject::connect(this->select_form, SIGNAL(command_unspecified()), this, SLOT(command_pending()));

    central_layout->addWidget(this->select_form);
    //central_layout->addWidget(this->job_ui);
    //central_layout->addWidget(this->tabs_widget);

    this->central_widget->setLayout(central_layout);
    this->setCentralWidget(this->central_widget);
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
