
/*
 * A Browser for QDebug Log Output
 * http://qt-project.org/wiki/Browser_for_QDebug_output
 *
 */
#ifndef LOG_TEXT_H
#define LOG_TEXT_H

#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QSizePolicy>

class LogText : public QPlainTextEdit{
public:
    LogText(QWidget *parent=0);
    QPlainTextEdit* text_area();
public slots:
    bool save_to_file(QString fname="");
    void appendText(QString str);
};

#endif // LOG_TEXT_H
