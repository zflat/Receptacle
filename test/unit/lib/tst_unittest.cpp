#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include "test_util_collection.h"
#include "test_log_text_page.h"
#include "test_log_emitter.h"
#include <QPointer>
#include <stdio.h>


int main(int argc, char *argv[]){
    // Construct application before running tests
    // http://stackoverflow.com/a/16711202
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);

    TestUtilCollection testutilcollection;
    QTest::qExec(&testutilcollection, argc, argv);

    TestLogText testlogtext;
    QTest::qExec(&testlogtext, argc, argv);

    TestLogEmitter testlogemitter;
    QTest::qExec(&testlogemitter, argc, argv);


    if(false){app.exec();}
    return(0);
}


#include "tst_unittest.moc"


// testrunner approach
// see http://stackoverflow.com/questions/1524390/what-unit-testing-framework-should-i-use-for-qt
