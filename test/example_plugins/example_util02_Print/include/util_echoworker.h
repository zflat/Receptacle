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

// util_echoworker.h

#ifndef UTIL_ECHOWORKER_H
#define UTIL_ECHOWORKER_H

#include <QRunnable>
#include <QObject>
#include "util_worker.h"

class UtilEchoWorker : public UtilWorker
{
    Q_OBJECT
public:
    void start();
};

#endif // UTIL_ECHOWORKER_H
