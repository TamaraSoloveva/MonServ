#pragma once

#include <QObject>
#include <QByteArray>
#include <QString>
#include "common.h"
#include "Pack.h"


class parseData : public QObject  {
    Q_OBJECT
public:
    explicit parseData( QObject *parent, const QByteArray & data, operationInfo *op, const int &sz )
        : data(data), op(op), opSize(sz){ };
    parseData(const parseData &other) = delete;
    parseData &operator=(const parseData &other) = delete;
    ~parseData() { }
    void parser();
private:
    QByteArray data;
    QString sData;
    in_Mon inPack;
    State state;
    int opSize;
    operationInfo *op;
signals:
    void showData( const QString &data);
    void printDataInField( const QString & marker, const QString &data);
};
