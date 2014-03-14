#include "widgets/log_text.h"

LogText::LogText(QWidget *parent=0) : QPlainTextEdit(parent){
    this->setReadOnly(true);
    this->setCursorWidth(8);
    this->setSizePolicy(QSizePolicy::Policy::Expanding,QSizePolicy::Policy::Expanding);
    this->resize(200, 200);
}

LogText::text_area(){
    return &this;
}

LogText::save_to_file(QString const fname=""){
    return false;
}
