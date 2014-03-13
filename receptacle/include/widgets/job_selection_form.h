#ifndef JOB_SELECTION_FORM_H
#define JOB_SELECTION_FORM_H


#include <QtGui>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QString>
#include "util_collection.h"

class JobSelectionForm: public QWidget{
    Q_OBJECT

public:
    JobSelectionForm(QWidget *parent=0);
    bool populate_command_options(UtilCollection* utils);

signals:
    void command_selected(QString commmand);
    void command_unrecognized(QString command);
    void command_unspecified();

public slots:
    void btn_pressed_handler();
    bool command(QString cmd);

protected:
    QLabel* label;
    QHBoxLayout* layout;
    QPushButton* btn;
    QComboBox* box;
    UtilCollection* utils;

};

#endif // JOB_SELECTION_FORM_H
