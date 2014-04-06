#ifndef COMPLEX_FORM_WIDGET_H
#define COMPLEX_FORM_WIDGET_H

#include <QWidget>

namespace Ui {
class ComplexFormWidget;
}

class ComplexFormWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ComplexFormWidget(QWidget *parent = 0);
    ~ComplexFormWidget();

private:
    Ui::ComplexFormWidget *ui;
};

#endif // COMPLEX_FORM_WIDGET_H
