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

#include "widgets/log_text.h"

LogText::LogText(QWidget *parent) : QPlainTextEdit(parent){
    this->setReadOnly(true);
    this->setCursorWidth(8);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

QPlainTextEdit* LogText::text_area(){
    return this;
}

bool LogText::save_to_file(QString fname){
    if(fname.isEmpty())
        return false;

    QFile file(fname);
    if(!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(
                    this,
                    tr("Error"),
                    QString(tr("<nobr>File '%1'<br/>cannot be opened for writing.<br/><br/>"
                               "The log output could <b>not</b> be saved!</nobr>"))
                    .arg(fname));
        return false;
    }

    QTextStream stream(&file);
    stream << this->text_area()->toPlainText();
    file.close();
    return true;
}


void LogText::appendText(QString str){
    this->text_area()->appendPlainText(str);
}
