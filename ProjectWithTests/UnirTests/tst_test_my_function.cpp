#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class test_my_function : public QObject
{
    Q_OBJECT

public:
    test_my_function();
    ~test_my_function();

private slots:
    void test_case1();

};

test_my_function::test_my_function()
{

}

test_my_function::~test_my_function()
{

}

void test_my_function::test_case1()
{
    // given: facts
    // when: call function to test
    // then: verify
    QCOMPARE(12, 15);
}

QTEST_MAIN(test_my_function)

#include "tst_test_my_function.moc"
