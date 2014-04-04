#ifndef SIMPLE_FORM_WIDGET_H
#define SIMPLE_FORM_WIDGET_H

#include <QWidget>

namespace Ui {
class SimpleFormWidget;
}

class SimpleFormWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SimpleFormWidget(QWidget *parent = 0);
    ~SimpleFormWidget();

private:
    Ui::SimpleFormWidget *ui;
};

#endif // SIMPLE_FORM_WIDGET_H
