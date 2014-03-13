#include <QString>
#include <QtTest>
#include <QCoreApplication>

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
}

void IntegrationTest::cleanupTestCase()
{
}

void IntegrationTest::testOpenCloseLauncher()
{
    QVERIFY2(true, "Failure");
}

QTEST_MAIN(IntegrationTest)

#include "tst_integrationtest.moc"
