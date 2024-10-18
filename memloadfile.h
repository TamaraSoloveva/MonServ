#ifndef MEMLOADFILE_H
#define MEMLOADFILE_H

#include <QObject>
#include "common.h"
#include "hexspinbox.h"
#include "baseCommandClass.h"

class MemotyOperationsTab : public QObject {
    Q_OBJECT
public:
    MemotyOperationsTab( const QString &txt1, const int &sz );
    MemotyOperationsTab( const QString &txt1, const QString &txt2, const int &sz);
    MemotyOperationsTab( const int &sz,  HexSpinBox *hspin, Debug_Operations_Class2 &dbgIn );
    MemotyOperationsTab( const int &sz,  HexSpinBox *hspin, const QString str, Debug_Operations_Class2 &dbgIn );
    void runOperation();

protected:
    int size;
    HexSpinBox *hspin;
    QString addr, data;
    QLineEdit *lEd;
    quint32 addrH;
    bool ok;
    Debug_Operations_Class2 *dbg;

    void checkAddress();



private:


    virtual void getCmdType() = 0;
    virtual void sendInformationAboutOp() = 0;
    virtual void packDataAndSend() = 0;


signals:
    void setAllEditsReady();
    void errorNoData(HexSpinBox *hspin);
    void sendMessage_report(const QString &tr);
    void sendMessage_log(const QString &tr);
    void sendMessage_status(const QString &tr);


};
//------------------------------------------------------------------------------------------------------------------
class MemoryOP : public MemotyOperationsTab {
    quint32 cmdType;
public:
    MemoryOP( const int &sz,  HexSpinBox *hspin, Debug_Operations_Class2 &dbgIn) :
                            MemotyOperationsTab{sz, hspin, dbgIn}, cmdType( READ_MEM_BYTE ) { }
private:
    void getCmdType() override;
    void sendInformationAboutOp() override;
    void packDataAndSend() override;
};
//------------------------------------------------------------------------------------------------------------------
class WriteOPMem : public MemotyOperationsTab {
    quint32 cmdType;
public:
    WriteOPMem( const int &sz,  HexSpinBox *hspin, const QString &dStr, Debug_Operations_Class2 &dbgIn) :
        MemotyOperationsTab{sz, hspin, dStr, dbgIn}, cmdType( WRITE_MEM_BYTE ){}
private:
    void getCmdType() override;
    void sendInformationAboutOp() override;
    void packDataAndSend() override;
    void getWriteData();
    quint32 Dt;


};
//------------------------------------------------------------------------------------------------------------------
class PortOP : public MemotyOperationsTab {
    quint32 cmdType;
public:
    PortOP( const int &sz,  HexSpinBox *hspin, Debug_Operations_Class2 &dbgIn) :
                            MemotyOperationsTab{sz, hspin, dbgIn}, cmdType(READ_PORT_BYTE) {}
private:
    void getCmdType() override;
    void sendInformationAboutOp() override;
    void packDataAndSend() override;

};

//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
class memLoadFile : public QObject
{
    Q_OBJECT
public:
    memLoadFile(QString flName);


private:
    void getFileSize();
    QString filename;
    QFile *qFl;
signals:
    void showMemFileSize( const size_t & sz);


};


#endif // MEMLOADFILE_H
