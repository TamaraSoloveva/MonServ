#ifndef BASECOMMANDCLASS_H
#define BASECOMMANDCLASS_H

#include <QtGlobal>
#include <QObject>

#include "Work_variables.h"

class BaseCommandClass : public QObject {
protected:
    int RetAdr[ 20 ];
    int StrNum;
public:
//    explicit BaseCommandClass( Monitor_Page_Class  * WrkFuncs );
//    virtual ~BaseCommandClass();

//    virtual void IOWrite( const quint32 &Adr, const quint32 &Dt, const int &Sz ) = 0;
    virtual void MemRead( const quint32 &Adr,  const int &Sz ) = 0;
    virtual void MemReadToFile( const quint32 &Adr, const QString &filename, const int &Sz ) = 0;
    virtual void IORead( const quint32 &Adr,  const int &Sz ) = 0;
//    virtual void AddData( const quint32 &Adr, const quint32 &Dt, const int &Sz ) = 0;
//    virtual bool CmpData( const quint32 &Dt1, const quint32 &Dt2, const int &Sz ) = 0;
//    virtual int Jmp( const QString &Lbl ) = 0;
//    virtual int Jz( const QString &Lbl, bool ZFl ) = 0;
//    virtual int Jnz( const QString &Lbl, bool ZFl ) = 0;
//    virtual int Call( const QString &Lbl, const int &i ) = 0;
//    virtual int Ret( const int &i ) = 0;
//    virtual bool CmpMem( const quint32 &Adr1, const quint32 &Adr2, const int &Sz ) = 0;
//    virtual void MovMem( const quint32 &RAdr, const quint32 &SAdr, const int &Sz ) = 0;
//    virtual void MovPort(const quint32 &RAdr, const quint32 &SAdr, const int &Sz ) = 0;
//    virtual void MovMemPort( const quint32 &RAdr, const quint32 &SAdr, const int &Sz ) = 0;
//    virtual void Label(  const QString &Lbl ) = 0;
//    virtual void Repeat ( const QString &Lbl, const int &RepTimes ) = 0;
//    virtual void LoadFl(  const quint32 &Adr, const QString &Name ) = 0;
//    virtual int LoadFilePart( const quint32 &Adr, const QString &Name, const int &size ) = 0;
//    virtual void LoadAndRunFl(  const quint32 &Adt, const QString &Name ) = 0;
//    virtual void JmpToAdr( const quint32 &Adr, bool WaitFl ) = 0;
//    virtual void Wait( const quint32 &Dt ) = 0;
//    virtual quint8 GetModuleType() = 0;
//    virtual bool GetScriptResult() = 0;
//    virtual void TextOutFunc( const QString &Text ) = 0;
//    virtual void WaitRestartFromMod() = 0;
//    virtual int Mod_pwr_on( const int &i ) = 0;
//    virtual int Mod_pwr_off( const int &i ) = 0;
//    virtual void RunApplication( const QString &AppName ) = 0;
//    virtual int RunAndWaitApplication( const QString &AppName, const QString &Params ) = 0;
//    virtual int RunAndCommunicationApp( const QString &AppName, const QString &Params  ) = 0;
//    virtual bool GetRepeatState() = 0;
//    virtual void SendToQNX( const QString &type, const QString &params ) = 0;

//    Monitor_Page_Class *MyComFunc;

};

class Debug_Operations_Class2 : public QObject {
    Q_OBJECT

public:
     void MemRead(const int &OP_TYPE, const quint32 &Adr,  const int &type );
     void MemWrite ( const int &OP_TYPE, const quint32 &Adr, const quint32 &Dt, const int &Sz, const int &type );
     Debug_Operations_Class2();
signals:
    void signalWriteCapture( const QString & msg);
    void signalWritePort( const QByteArray &arr );
    void signalSetOutputMode( const int &new_mode );

};



class Debug_Operations_Class : public BaseCommandClass  {
    Q_OBJECT
private:
    int SendProtocolMessage( const quint32 &type, const quint32 &addr, const quint32 &data, const quint32 &wrkMode_new);


public:
    void MemRead(const quint32 &Adr,  const int &type ) override;
    void IORead( const quint32 &Adr,  const int &Sz ) override;
    void MemReadToFile( const quint32 &Adr, const QString &filename, const int &Sz ) override;
signals:
    void signalWriteCapture( const QString & msg);
    void signalWritePort( const QByteArray &arr );

};

#endif // BASECOMMANDCLASS_H
