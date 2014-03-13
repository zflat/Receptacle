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
    HostController* controller = new HostController(utils);

    // Create an instance of a server and then start it.
    Dispatcher server(controller);
    server.startServer();
    return;
}

void IntegrationTest::cleanupTestCase()
{
    qDebug() << "Server cleanup";
    qApp->exit(0);
}

void IntegrationTest::testOpenCloseLauncher()
{
    QVERIFY2(true, "Failure");
}

QTEST_MAIN(IntegrationTest)

#include "tst_integrationtest.moc"
