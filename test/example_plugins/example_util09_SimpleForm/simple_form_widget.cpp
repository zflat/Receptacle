#include "simple_form_widget.h"
#include "ui_simple_form_widget.h"

SimpleFormWidget::SimpleFormWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimpleFormWidget)
{
    ui->setupUi(this);
}

SimpleFormWidget::~SimpleFormWidget()
{
    delete ui;
}
