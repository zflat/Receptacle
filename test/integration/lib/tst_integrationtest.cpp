#include <QString>
#include <QtTest>
#include <QCoreApplication>


#include "dispatcher.h"
#include "util_collection.h"
#include "host_controller.h"

class IntegrationTest : public QObject
{
    Q_OBJECT

public:
    IntegrationTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testOpenCloseLauncher();
private:
    Dispatcher* server;
    HostController* host;
};

IntegrationTest::IntegrationTest()
{
}

void IntegrationTest::initTestCase()
{
    /*
    int argc =0;
    char* argv = new char[0];
    QApplication app(argc, &argv);
    app.setQuitOnLastWindowClosed(false);
    */

    qApp->setQuitOnLastWindowClosed(false);
    UtilCollection* utils = new UtilCollection();
    host = new HostController(utils);

    // Create an instance of a server and then start it.
    server = new Dispatcher(host);
    server->startServer();
    return;
}

void IntegrationTest::cleanupTestCase()
{
    qDebug() << "Server cleanup";
    delete server;
    qApp->exit(0);
}

void IntegrationTest::testOpenCloseLauncher()
{
    server->queue_request("cmd");
    host->kill_job();
    QTRY_VERIFY_WITH_TIMEOUT(!server->queue_busy(), 5000);
    QVERIFY2(true, "Failure");
}

QTEST_MAIN(IntegrationTest)
/*
int main(int argc, char *argv[])
{
    IntegrationTest test1;
    QTest::qExec(&test1, argc, argv);

    return 0;
}
*/


#include "tst_integrationtest.moc"



// testrunner approach
// see http://stackoverflow.com/questions/1524390/what-unit-testing-framework-should-i-use-for-qt
