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
    bool select_job(QString cmd);

private:
    QLabel* label;
    QHBoxLayout* layout;
    QPushButton* btn;
    QComboBox* box;

};

#endif // JOB_SELECTION_FORM_H
