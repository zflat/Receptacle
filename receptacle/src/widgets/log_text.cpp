#include "widgets/log_text.h"

LogText::LogText(QWidget *parent) : QPlainTextEdit(parent){
    this->setReadOnly(true);
    this->setCursorWidth(8);
    //QSizePolicy::Policy* policy_expanding = new QSizePolicy(QSizePolicy::Policy::Expanding);

    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->resize(200, 200);
}

QPlainTextEdit* LogText::text_area(){
    return this;
}

bool LogText::save_to_file(QString fname){
    return false;
}


void LogTextPage::appendText(QString str){
    this->text_area->appendPlainText(str);
}
