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


// signal_counter.h

#ifndef SIGNAL_COUNTER_H
#define SIGNAL_COUNTER_HER_H

#include <QObject>

/**
 * @brief The SignalCounter class is a simplified version of QSignalSpy.
 */
class SignalCounter : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief SignalCounter constructor connects to the given signal and starts counting at 0
     * @param object QObject that emits the signal to count
     * @param signal that is counted
     */
    SignalCounter(const QObject * object, const char * signal):c(0){
        QObject::connect(object, signal, this, SLOT(increment()));
    }

    /**
     * @brief Current count of signals that have been emitted
     * @return int
     */
    int count(){return c;}

private slots:
    /**
     * @brief Connect the increment slot to a signal to track
     */
    void increment(){c++;}

protected:
   int c;

};

#endif // SIGNAL_COUNTER_H
