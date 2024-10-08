#ifndef TSTCOMCLASS_H
#define TSTCOMCLASS_H
#include <QObject>
#include <QFile>
#include <QDebug>
#include <QDate>
#include <QDateTime>
#include <QTime>
#include <QMessageBox>
#include <QTextCodec>


class wrInfoClass : public QObject
{
    Q_OBJECT
private:
    bool detectFl, msgStart, msgAnswRes;
    int cnt;
    int bigNindex;
    bool isKredo;
    bool isNenormDet;
    QString ConvertMode;
    QByteArray okHdr1, okHdr2, ansHdr, tmpA;
    QByteArray VScode, ansKredo, noNormOEM, noNormANSI;
    int checkBArray(QByteArray, int);
    int cmpWithOkHdr(QByteArray);
    int cmpWithAnswArr(QByteArray);
    int cmpWithAnsKredo(QByteArray);
    int cmpWithCodesInIni(QByteArray ba);
    QByteArray modWaitMsg;
    QString msgKredoWait, msgKredoSb;
    QTextCodec *codec;
    bool flWaitNoNorm;
    int cmpFunc(QByteArray ba1, QByteArray ba2, int sz);

public:
    QByteArray outBA;
    QVector<QByteArray>modCodes;
    explicit wrInfoClass(QString outC, QObject *parent = 0);

signals:
    void signalReadyToShow(QByteArray);
    void signalReadyToShowRus(QString);
    void signalCodeDetect(QByteArray);
    void signalWriteAnswerCode(QByteArray);
    void signalReReadModuleCodes( QVector<QByteArray> *);
    void signalStopAllOperations( QString);
    void signalSetKredoMode();
    void signalStopKredoMode();
    void signalInsertInQueue(QByteArray);
    void signalNoNormReceived();
    void signalReadyToShowRed(QByteArray);

public slots:
    void slotReceiveArray( QByteArray );
    void slotTurnOnDetectMode() { detectFl = true; }
    void slotTurnOffDetectMode() { detectFl = false; }
    void slotSetOutputCoding(QString mode) {ConvertMode = mode;}
    void slotSetWaitNoNormFlag(bool st) { flWaitNoNorm = st; }
    void slotDownAllComFlags();


private slots:
    void slotSetKredoMode() {isKredo = true; }

};

#endif // TSTCOMCLASS_H
