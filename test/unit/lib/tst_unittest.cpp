#include <QString>
#include <QtTest>
#include <QCoreApplication>

class UnitTest : public QObject
{
    Q_OBJECT

public:
    UnitTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
};

UnitTest::UnitTest()
{
}

void UnitTest::initTestCase()
{
}

void UnitTest::cleanupTestCase()
{
}

void UnitTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

// QTEST_APPLESS_MAIN(UnitTest)

#include "test_util_collection.h"
#include "test_log_text_page.h"
#include "test_log_emitter.h"
#include <QPointer>

#include "log_emitter.h"

QPointer<LogEmitter> logger;
void log_handler_forwarder(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    if(logger)
        logger->publish_message(type, context, msg);
}


int main(int argc, char *argv[]){
    qInstallMessageHandler(0);
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);

    TestUtilCollection testutilcollection;
    QTest::qExec(&testutilcollection, argc, argv);

    TestLogTextPage testlogtextpage;
    QTest::qExec(&testlogtextpage, argc, argv);


    qInstallMessageHandler(log_handler_forwarder);
    TestLogEmitter testlogemitter;
    QTest::qExec(&testlogemitter, argc, argv);
    qInstallMessageHandler(0);


    // Construct application before running tests
    // http://stackoverflow.com/a/16711202
    // app.exec();
    return(0);
}


#include "tst_unittest.moc"


// testrunner approach
// see http://stackoverflow.com/questions/1524390/what-unit-testing-framework-should-i-use-for-qt
