#include "widgets/log_text.h"

LogTextPage::LogTextPage(QWidget *parent) : QWidget(parent){
    this->layout = new QVBoxLayout;
    this->text_area = new LogText(this);
    this->setSizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored);
}
