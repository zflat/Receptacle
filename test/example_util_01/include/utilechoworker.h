#ifndef UTILECHOWORKER_H
#define UTILECHOWORKER_H

#include <QObject>
#include <QRunnable>

class UtilEchoWorker : public QObject, public QRunnable {
    Q_OBJECT
public:
    UtilEchoWorker();

signals:
    // notify when we're done
    void result(int ret_val);

protected:
    void run();

};

#endif // UTILECHOWORKER_H
