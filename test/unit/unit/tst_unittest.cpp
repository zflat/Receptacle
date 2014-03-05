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

// QTEST_APPLESS_MAIN(UnitTest)

#include "test_util_collection.h"

int main(int argc, char *argv[]){
    TestUtilCollection testutilcollection;
    QTest::qExec(&testutilcollection, argc, argv);

    return(0);
}

#include "tst_unittest.moc"


// testrunner approach
// see http://stackoverflow.com/questions/1524390/what-unit-testing-framework-should-i-use-for-qt
