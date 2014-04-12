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


#ifndef LABEL_FOR_H
#define LABEL_FOR_H

#include <QWidget>
#include <QLabel>
// based on http://qt-project.org/wiki/Make-a-QLabel-Clicka
class LabelFor : public QLabel{

Q_OBJECT

public:
    explicit LabelFor( const QString& text ="", QWidget* on_click_buddy=NULL , QWidget * parent = 0);
    ~LabelFor();

signals:
    void clicked();

protected:
    void mousePressEvent ( QMouseEvent * event ) ;

    /**
     * @brief click_buddy
     *   QWidget that gets focus when the label is clicked
     */
    QWidget* click_buddy;
};

#endif // LABEL_FOR_H
