/*

Copyright 2014 William Wedler

This file is part of Receptacle

Receptacle is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Receptacle is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Receptacle.  If not, see <http://www.gnu.org/licenses/>.

*/


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

    static const char WARN_INDICATION_STYLE[];
    static const char ERR_INDICATION_STYLE[];

signals:
    void command_selected(QString commmand);
    void command_unrecognized(QString command);
    void command_unspecified();

public slots:
    void btn_pressed_handler();
    bool command(QString cmd);

    /**
     * @brief Visual indication that the message type has been published
     * @param type
     *   QtMsgType indicating the error level
     */
    void indicate_msg_level(QtMsgType type);

protected:
    QLabel* label;
    QHBoxLayout* layout;
    QPushButton* btn;
    QComboBox* box;
    UtilCollection* utils;

};

#endif // JOB_SELECTION_FORM_H
