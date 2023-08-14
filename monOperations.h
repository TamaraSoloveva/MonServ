#pragma once

#include "Pack.h"
#include "common.h"



class monOperations  : public QObject {
    Q_OBJECT
public:
    monOperations( QObject *parent, const operationInfo & op, const quint32 & addIn,
             const int & szIn, const quint32 &dataOut = 0 ) :
             QObject(parent), opInfo(op), addr(addIn), size(szIn), data(dataOut)  { }
    virtual ~monOperations() { }
    void begin_operation();

private:
    in_Mon inPack;
    out_Mon outPack;
    State mode;
    quint32 addr;
    quint32 data;
    int size;
    operationInfo opInfo;

    void packData();
signals:
    void signalWriteArrayToPort( QByteArray array );
};
