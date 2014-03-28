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


/*
 * Example code: A Browser for QDebug Log Output
 * http://qt-project.org/wiki/Browser_for_QDebug_output
 *
 */
#ifndef LOG_TEXT_H
#define LOG_TEXT_H

#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QSizePolicy>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QCloseEvent>
#include <QKeyEvent>

class LogText : public QPlainTextEdit{
public:
    LogText(QWidget *parent=0);
    QPlainTextEdit* text_area();
public slots:
    bool save_to_file(QString fname);
    void appendText(QString str);
};

#endif // LOG_TEXT_H
