#ifndef OUTTHREAD_H
#define OUTTHREAD_H

#include <QThread>
#include <QQueue>
#include <QMutex>
#include <QMutexLocker>
#include <QTextCodec>

#include "common.h"

#define DETECT_MODE 0
#define SIMPLE_MODE 1
#define B4_MODE     2
#define KREDO_ANS   3

#define PROTOKOL_MSG_SIZE   8
#define B4_MSG_SIZE         5

#define MOD_DETECT_MODE 0
#define B4_DETECT_MODE  1
#define MOD_DETECTED    3


// Пример реализации класса
class Q_PARSER_CLASS : public QObject {
    Q_OBJECT

public:
    Q_PARSER_CLASS( QMutex *m, QQueue<QByteArray>* q, QVector<QByteArray> *cmdVec ) ;
    ~Q_PARSER_CLASS();

public slots:
    void process();
    void setOutputMode( const int &new_mode );
    void stopOperation();

signals:
    void finished();
    void parseInputArray( const QByteArray &ba);
    void writeDataToCom( const QByteArray &ba );
    void signalReadyToShow(const QByteArray &outBA);
    void writeErrorMsg( const QString &msg);
    void writeOKMsg( const QString &msg);
    void readMemValueShow( const QByteArray &rdVal, bool isMem  );
private slots:
    void slotParseInputArray( const QByteArray &ba );
private:
    QMutex *mutex;
    QQueue<QByteArray>* outputQ;
    QVector<QByteArray> *modCodes;
    QTextCodec *codec;

    bool isNenormDet, detectFl, msgStart, msgAnswRes;
    QByteArray okHdr1, okHdr2, ansHdr, tmpA, outBA, bufBA;
    int cnt;

    void cleanStatusObjects(const int &mode);
    void funcFormAnswer( const QByteArray &ba );

    int checkDataString(const QByteArray &tmpArr,  const int &count, const int &mode);
    int cmpWithOkHdr(const QByteArray &tmpS, const int &count);
    int cmpWithAnswArr(const QByteArray &tmpArr, const int &count);
    int output_mode;

};

#endif // OUTTHREAD_H
