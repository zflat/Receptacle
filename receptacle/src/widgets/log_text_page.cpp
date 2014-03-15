#include "widgets/log_text.h"
#include <QDebug>

LogTextPage::LogTextPage(QWidget *parent) : QWidget(parent){
    QVBoxLayout* layout = new QVBoxLayout();
    this->setLayout(layout);
    //this->page_layout = new QVBoxLayout();
    this->text_area = new LogText(this);
    this->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
}

void LogTextPage::appendText(QString str){
    this->text_area->appendPlainText(str);
}
