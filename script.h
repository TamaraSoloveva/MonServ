#pragma once
#include <QObject>
#include <QTableWidget>
#include <iostream>
#include <fstream>

class Script : public QObject {
    Q_OBJECT
public:
    explicit Script(const QString & fl ) : dbgName(fl){  fOpenButton(); }

public slots:
    void fOpenButton();


private:
    QString dbgName;
    QVector<QString>lineVec;
    QVector<QVector<QString>>v;




signals:
    void addLine(const QVector<QVector<QString>> & line);



};
