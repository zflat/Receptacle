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



#ifndef ABOUT_DIALOG_H
#define ABOUT_DIALOG_H

#include <QApplication>
#include <QDialog>
#include <QIcon>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>


class QLabel;
class QPushButton;

class AboutDialog : public QDialog{
    Q_OBJECT

public:
    AboutDialog(const QString &plugins_path, const QStringList &plugin_fileNames,
                QWidget *parent = 0);

private:
    QLabel *label;
    QPushButton *okButton;
};

#endif // ABOUT_DIALOG_H
