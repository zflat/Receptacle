#include "complex_form_widget.h"
#include "ui_complex_form_widget.h"

ComplexFormWidget::ComplexFormWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComplexFormWidget)
{
    ui->setupUi(this);
}

ComplexFormWidget::~ComplexFormWidget()
{
    delete ui;
}
