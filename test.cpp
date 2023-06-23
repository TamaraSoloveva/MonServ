#include <QtTest/QTest>

#include <QApplication>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "test_smart.h"
#include "test_qlineedit.h"

using namespace std;

int main(int argc, char *argv[])
{
    freopen("testing.log", "w", stdout);
    QApplication a(argc, argv);
    QTest::qExec(new Test_Smart, argc, argv);
    cout << endl;
    QTest::qExec(new Test_QLineEdit, argc, argv);
    return 0;
}


#include <QtTest>
#include <QtGui>
#include "test_qlineedit.h"

void Test_QLineEdit::edit()
{
    QLineEdit a;
    QTest::keyClicks(&a, "abCDEf123-");

    QCOMPARE(a.text(), QString("abCDEf123-"));
    QVERIFY(a.isModified());
}
