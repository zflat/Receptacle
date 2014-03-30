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

// util_runner.h

#ifndef UTIL_RUNNER_H
#define UTIL_RUNNER_H

#include <QRunnable>
#include <QObject>
#include <QSignalSpy>
#include "util_worker_interface.h"
#include "log_emitter.h"

class UtilRunner : public QObject, public QRunnable
{
    Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param cmd QString associated with the worker
     * @param util_worker implements the utility business logic for the given command
     * @param err_emitter LogEmitter used to monitor the qDebug log levels
     */
    UtilRunner(QString cmd, UtilWorkerInterface* util_worker, LogEmitter* err_emitter);

    /**
     * @brief Accessor method for the command associated with this worker
     * @return QString command
     */
    QString command();

    /**
     * @brief Determine if the utility shall be hidden or shown based on current state
     * @return bool True if the utilility shall be hidden, False otherwise
     */
    bool is_hidden();
protected:

    /**
     * @brief Perform time-consuming task in a background thread when the thread pool queues it.
     */
    void run();

signals:
    /**
     * @brief Notify when the worker execution has finished
     * @param ret_val int Return value code
     */
    void result(int ret_val);
protected:
    QString command_str;
    UtilWorkerInterface* worker;
    QSignalSpy err_flag;
    QSignalSpy warn_flag;
};

#endif // UTIL_RUNNER_H