#pragma once

#include <QObject>
#include <QtTest/QTest>
#include <iostream>
#include <cstdlib>
#include <cstdio>


class Test_QLineEdit : public QObject
{
    Q_OBJECT
private slots:
    void edit();

};



class Smart : public QObject
{
    Q_OBJECT
public:
    explicit Smart(QObject *parent, const QStringList& list);

public slots:
    int max(int a, int b);
    int min(int a, int b);

};


