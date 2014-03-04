#include <QString>
#include <QtTest>

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

QTEST_APPLESS_MAIN(UnitTest)

#include "tst_unittest.moc"
