#include <QtTest>
#include <QCoreApplication>
#include <QDebug>

// add necessary includes here
#include "../MyApplication/geometry.h"
//#include "geometry.h" // TODO: simplify with INCLUDEPATH

//https://doc.qt.io/qt-6/qtest-overview.html

class TestMyFunctions : public QObject
{
    Q_OBJECT

public:

private slots:
    // setup/cleanup
    //        initTestCase() will be called before the first test function is executed.
    //        initTestCase_data() will be called to create a global test data table.
    //        cleanupTestCase() will be called after the last test function was executed.
    //        init() will be called before each test function is executed.
    //        cleanup() will be called after every test function.
    void initTestCase();
    void cleanupTestCase();

    // my tests
    void test_case1();
    void test_case2();
    void test_case3();
    void test_triangle_area();
};

void TestMyFunctions::initTestCase()
{
    qDebug("Called before everything else.");
}

void TestMyFunctions::cleanupTestCase()
{
    qDebug("Called after all mys tests.");
}

void TestMyFunctions::test_case1()
{
    QVERIFY(3 == 3);
}

void TestMyFunctions::test_case2()
{
    QCOMPARE(0.3, 3*0.1);
}

void TestMyFunctions::test_case3()
{
    QCOMPARE_EQ(0.3, 3*0.1);
}

void TestMyFunctions::test_triangle_area(){
    qreal a = 4.0;
    qreal b = 5.0;
    qreal c = 3.0;
    qreal area = triangle_area(a, b, c);
    QCOMPARE_EQ(6.0, area);
}

QTEST_MAIN(TestMyFunctions)

#include "tst_testmyfunctions.moc"
