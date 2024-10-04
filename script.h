
#pragma once

#include "common.h"

class DbgClass {
public:
    explicit DbgClass(const QString &name, const QMap<QString, useFields> &cmdMap = {});
    ~DbgClass();
     QVector<QVector<QString>>  showTable();

private:
     QFile qFile;
     QVector<QString> formVector( const QString &str);
     QMap<QString, useFields>mCmd;
     QVector<QString>lineVec;
     QVector<QVector<QString>> linesToRunAndShow;

};
