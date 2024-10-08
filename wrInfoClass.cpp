#include "wrInfoClass.h"
#include "Work_variables.h"

wrInfoClass::wrInfoClass(QString outC, QObject *parent ) : QObject(parent)
{
    modCodes.clear();
    detectFl = false;
    msgStart = false;
    msgAnswRes = false;
    isNenormDet = false;
    flWaitNoNorm = true;
    okHdr1 = "0F0E0156";
    okHdr2 = "0F0E0157";
    ansHdr = "B431B43900";
    ansKredo = "0F0E015A";
    VScode = "0F0E01570F0E014C";
    noNormOEM = "8D858D8E908C80";
    noNormANSI = "CDC5CDCED0CCC0";
    bigNindex=0;
    cnt=0; //общее количество символов в строке для разбора
    ConvertMode = outC;
    #ifdef  Q_OS_WIN32
       msgKredoWait = "\n>Модуль в ожидании команды\n>\n";
       msgKredoSb = "\n>Сбой в технологическом канале\n";
    #elif defined Q_OS_UNIX
       msgKredoWait = "\x0D>Модуль в ожидании команды\x0D>\x0D";
       msgKredoSb = "\x0D>Сбой в технологическом канале\x0D";
    #endif




}


int wrInfoClass::cmpWithOkHdr(QByteArray ba)  {
    QByteArray tmp;
    for (int i=0; i<4; i++)  {
        tmp.append( ba.at(i));
    }

    tmp = tmp.toHex().toUpper();
    if (tmp == okHdr1)
            return 0;
    else if (tmp == okHdr2)
        return 2;
    else
        return 1;
}

int wrInfoClass::cmpWithAnswArr(QByteArray ba) {
    ba = ba.toHex().toUpper();
    if (ba == ansHdr)
        return 0;
    else
        return 1;
}

int wrInfoClass::cmpWithAnsKredo(QByteArray ba) {
    ba = ba.toHex().toUpper();
    if (ba == ansKredo)
        return 0;
    else
        return 1;
}

int wrInfoClass::cmpWithCodesInIni(QByteArray ba) {
    QVector<QByteArray>baVec;
    ba = ba.toHex().toUpper();
    //получаем все коды из ini-файла
    emit signalReReadModuleCodes( &baVec);
    int sz = baVec.size();
    int eq=0;
    //перебираем эти коды, если есть что перебирать
    for (int i=0; i<sz; i++) {
        if (ba == baVec.at(i)) {
            eq++;
            break;
        }
    }
    if (eq !=0 ) {
        if (ba == VScode)
            return 2;
        else
            return 0;
    }
    else
        return 1;
}

int wrInfoClass::checkBArray(QByteArray ba, int mode) {
    int rV=0;
    switch (mode) {
    case DETECT_MODE:
        //чтобы признать код посылкой, пусть совпадут первые 4 байта
        rV=cmpWithOkHdr(ba);
        break;
    case SIMPLE_MODE:
        rV=cmpWithCodesInIni(ba);
        break;
    case B4_MODE:
        rV=cmpWithAnswArr(ba);
        break;
    case KREDO_ANS:
        rV = cmpWithAnsKredo(ba);
        break;
    }
    return rV;
}

int wrInfoClass::cmpFunc(QByteArray ba1, QByteArray ba2, int sz) {
    for (int i=0; i<(sz*2); i++) {
        if (ba1.at(i) != ba2.at(i))
            return -1;
    }
    return 0;
}

void wrInfoClass::slotReceiveArray( QByteArray ba ){
    QByteArray baTemp;
    const char *s = ba.data();
    int len = ba.size();
    int retV=0;

    for (int i=0; i<len; i++) {
        if ( isNenormDet ) {
            tmpA.append(s[i]);
            cnt++;
            baTemp = tmpA;
            baTemp = baTemp.toHex().toUpper();
            if ((cmpFunc(baTemp, noNormOEM, cnt) == -1) && (cmpFunc(baTemp, noNormANSI, cnt) == -1)) {
                cnt=0;
                isNenormDet=false;
                outBA+=tmpA;
                tmpA.clear();
                continue;
            } else {
                if (cnt==7) {
                    emit signalNoNormReceived();
                    emit signalReadyToShow(outBA);
                    emit signalReadyToShowRed(tmpA);
                    cnt=0;
                    isNenormDet=false;
                    tmpA.clear();
                    outBA.clear();
                }
                continue;
            }

//            if (cnt == 7) {
//                baTemp = baTemp.toHex().toUpper();
//                if (baTemp == noNormOEM ) {
//                    emit signalNoNormReceived();
//                    emit signalReadyToShow(outBA);
//                    emit signalReadyToShowRed(tmpA);
//                    outBA.clear();
//                }
//                else {
//                    cnt=0;
//                    outBA+=tmpA;
//                    tmpA.clear();
//                    isNenormDet=false;
//                    i = bigNindex;
//                    continue;
//                }
//                tmpA.clear();
//                cnt=0;
//                isNenormDet=false;
//            } else continue;
        }
        else if (flWaitNoNorm && !isNenormDet) {
            if (((unsigned char)s[i] == 0x8d)  || ((unsigned char)s[i] == 0xCD))  {
                isNenormDet = true;
                tmpA.append(s[i]);
                bigNindex=i;
                cnt++;
                continue;
            }
        }

        if (msgStart) {
            //первая 0F получена
            tmpA.append(s[i]);
            cnt++;
            if (isKredo && (cnt == 4)) {
                retV = checkBArray(tmpA, KREDO_ANS);
                if (retV == 0) {
                    if (ConvertMode == "OEM") {
                        codec = QTextCodec::codecForName("cp866");
                        modWaitMsg = codec->fromUnicode(msgKredoWait);
                    }
                    emit signalInsertInQueue(modWaitMsg);
                    emit signalStopAllOperations("b4");
                    tmpA.clear();
                    cnt=0;
                    msgStart=false;

                }
            }
            if (cnt==8) {
                if (detectFl) {
                    //режим определения кода модуля
                    retV = checkBArray(tmpA, DETECT_MODE);
                    if (retV == 0) {
                        //обычный модуль
                        emit signalCodeDetect( tmpA  );
                        emit signalWriteAnswerCode(tmpA);
                        emit signalStopKredoMode();
                    }
                    else if (retV == 2) {
                        //КРЕДО_3VS
                        emit signalSetKredoMode();
                        emit signalCodeDetect( tmpA );
                        emit signalWriteAnswerCode("KREDO");
                    }
                    else {
                        outBA += tmpA;
                    }
                }else {
                    //обычный режим
                    retV = checkBArray(tmpA, SIMPLE_MODE);
                    if (retV == 0) {
                        //обычный модуль
                        emit signalWriteAnswerCode(tmpA);
                        emit signalStopKredoMode();
                    }
                    else if (retV == 2) {
                        emit signalSetKredoMode();
                        emit signalWriteAnswerCode("KREDO");

                    }
                    else {
                        outBA += tmpA;
                    }
                }
                tmpA.clear();
                cnt=0;
                msgStart=false;
            }
        }
        else if ((s[i] == 0xF) && !msgStart) {
            tmpA.append(s[i]);
            cnt++;
            msgStart=true;
        }
        else if (((unsigned char)s[i] == 0xb4) && !msgAnswRes){
            msgAnswRes = true;
            tmpA.append(s[i]);
            cnt++;
        }
        else if (msgAnswRes) {
            //получили от модуля ответ, что всё ок
            tmpA.append(s[i]);
            cnt++;
            if (cnt == 5) {
                if (!checkBArray(tmpA, B4_MODE)) {
                    codec = QTextCodec::codecForName("cp1251");
                    modWaitMsg = codec->fromUnicode(msgKredoWait);
                    emit signalInsertInQueue(modWaitMsg);
                    emit signalStopAllOperations("b4");
                }else {
                    outBA += tmpA;
                }
                tmpA.clear();
                cnt=0;
                msgAnswRes=false;
            }
        }
        else {
            outBA.append(s[i]);
        }
    }
    emit signalReadyToShow(outBA);
    outBA.clear();
}


void wrInfoClass::slotDownAllComFlags() {
     isNenormDet=false;
     detectFl=false;
     msgStart=false;
     msgAnswRes=false;
     tmpA.clear();
     cnt=0;
     bigNindex=0;
}
