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

int main(int argc, char *argv[]){

    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);

    TestUtilCollection testutilcollection;
    QTest::qExec(&testutilcollection, argc, argv);

    TestLogTextPage testlogtextpage;
    QTest::qExec(&testlogtextpage, argc, argv);

    return(0);

    // Construct application before running tests
    // http://stackoverflow.com/a/16711202
    app.exec();
}


#include "tst_unittest.moc"


// testrunner approach
// see http://stackoverflow.com/questions/1524390/what-unit-testing-framework-should-i-use-for-qt
