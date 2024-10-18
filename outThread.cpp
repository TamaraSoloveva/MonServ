#include "outThread.h"
#include <QDebug>
// Реализации методов класса


Q_PARSER_CLASS::Q_PARSER_CLASS(QMutex *m, QQueue<QByteArray> *q, QVector<QByteArray> *cmdVec) : mutex(m),
                                        outputQ(q), modCodes(cmdVec), output_mode(OUT_DATA_MODE)  {

    connect( this, &Q_PARSER_CLASS::parseInputArray, this, &Q_PARSER_CLASS::slotParseInputArray );
    isNenormDet = detectFl= msgStart = msgAnswRes= false;
    tmpA.clear();
    bufBA.clear();
    ansHdr.clear();

    cnt = 0;
}

Q_PARSER_CLASS::~Q_PARSER_CLASS() {
 }

void Q_PARSER_CLASS::process() {
    QByteArray ba;
    while (1) {
        QMutexLocker lock(mutex);
        ba.clear();
        while (!outputQ->isEmpty() )
        {
            ba+= outputQ->dequeue();
        }
        if ( !ba.isEmpty()) emit parseInputArray(ba);
    }
 //    emit finished();
}

void Q_PARSER_CLASS::stopOperation() {
    setOutputMode(OUT_DATA_MODE);
    tmpA.clear();
}

int Q_PARSER_CLASS::cmpWithOkHdr(const QByteArray &tmpArr, const int &count )  {
    int res = 1;
    QByteArray tmpPart;
    for (int i = 0; i< modCodes->size(); ++i) {
        tmpPart = modCodes->at(i).mid(0, count);
        if ( tmpPart == tmpArr ) {
            res = 0;
            break;
        }
    }
    return res;
}

int Q_PARSER_CLASS::cmpWithAnswArr(const QByteArray &tmpArr, const int &count) {
    QByteArray answerMsg = "B431B43900";
    int res = 1;
    QByteArray tmpPart = answerMsg.mid(0, count) ;
    if ( tmpPart.compare(tmpArr, Qt::CaseInsensitive) )
        res = 0;
    return res;
}

int Q_PARSER_CLASS::checkDataString(const QByteArray &tmpArr,  const int &count, const int &mode ) {
    int rV=0;
    switch (mode) {
    case DETECT_MODE:
        rV=cmpWithOkHdr(tmpArr, count);
        break;
    case SIMPLE_MODE:
       // rV=cmpWithCodesInIni(tmpArr);
        break;
    case B4_MODE:
        rV=cmpWithAnswArr(tmpArr, count);
        break;
    /*case KREDO_ANS:
        //rV = cmpWithAnsKredo(tmpArr);
        break;*/
    }
    return rV;
}

void Q_PARSER_CLASS::cleanStatusObjects(const int &mode) {    

    switch(mode) {
    case MOD_DETECT_MODE:        
        msgStart = false;
        outBA.append(tmpA);
        break;
    case MOD_DETECTED:
        msgStart = false;
        break;
    case B4_DETECT_MODE:
        outBA.append(tmpA);
        msgAnswRes = false;
        break;

    }
    tmpA.clear();
    cnt=0;
}

void Q_PARSER_CLASS::funcFormAnswer( const QByteArray &ba ) {
    QByteArray answBA = ba.mid(4, 4);
    emit writeDataToCom(answBA);
}

void Q_PARSER_CLASS::setOutputMode( const int &new_mode ){
    output_mode = new_mode;
}

// посимвольный перебор всех пришедших данных
void Q_PARSER_CLASS::slotParseInputArray( const QByteArray &ba ) {    
    int retV=0;
    for (int i=0; i< ba.size(); i++) {
        switch(output_mode) {
        case OUT_DATA_MODE:
            if (msgStart) {
                tmpA.append(ba[i]);
                cnt++;
                if (cnt == PROTOKOL_MSG_SIZE) {
                //если  retV=1, значит, строки не равны
                    retV = checkDataString(tmpA, cnt, DETECT_MODE );
                    if (retV)
                        cleanStatusObjects(MOD_DETECT_MODE);
                    else {
                        funcFormAnswer(tmpA);
                        cleanStatusObjects(MOD_DETECTED);
                    }
                }
            }
            else if (msgAnswRes) {
                tmpA.append(ba[i]);
                cnt++;
                retV = checkDataString(tmpA, cnt, B4_MODE);
                if (retV)
                    cleanStatusObjects(B4_DETECT_MODE);
                else {
                    if (cnt == B4_MSG_SIZE) {
                        tmpA = "\n\r>Модуль в ожидании команды\n\r>";
                        codec = QTextCodec::codecForName("cp1251");
                        tmpA = codec->fromUnicode(tmpA);
                        outBA.append(tmpA);
                        cleanStatusObjects(B4_DETECT_MODE);
                    }
                }

            }
            else if ((ba[i] == 0xF) && !msgStart) {
                tmpA.append(ba[i]);
                cnt++;
                msgStart=true;
              }
            else if (((unsigned char)ba[i] == 0xb4) ) {
                tmpA.append(ba[i]);
                cnt++;
                msgAnswRes = true;
              }
            else {
                outBA.append(ba[i]);
            }
            emit signalReadyToShow(outBA);
            outBA.clear();
            break;

        case READ_MEM_MODE:
            if (static_cast<uchar>(ba.at(i)) == 0xb3 ) {
                emit writeErrorMsg(tr("Ошибка контрольной суммы"));

            }
            else {
                ansHdr.push_back(ba.at(i));
                if (ansHdr.size() == 7) {
                    int ChSm1 = 0, ChSm2 = 0;
                    for (int j=0; j < 4; ++j) {
                        ChSm1 += static_cast<uchar>(ansHdr.at(j));
                        bufBA.push_back(ansHdr.at(j));
                    }
                    ChSm2 = ansHdr.at(5);
                    ChSm2 <<= 8;
                    ChSm2 |= ansHdr.at(4);
                    if (ChSm1 != ChSm2 ) {
                        emit writeErrorMsg(tr("Не сошлась контр.сум. пакета"));
                    }
                    else {
                        if (static_cast<uchar>(ansHdr.at(6)) != 0xb2) {
                            emit writeErrorMsg(tr("Не получен маркер успешного окончания"));

                        }
                        else {
                            QByteArray::iterator itr = bufBA.end();
                            QByteArray revers;
                            for (itr = bufBA.end(); itr > bufBA.begin(); --itr)
                                revers.push_back(*itr);
                            emit readMemValueShow(revers, true);
                            qDebug() << revers;

                        }



                    }
                    setOutputMode(OUT_DATA_MODE);
                    bufBA.clear();
                    ansHdr.clear();



                }


            }
            break;


        case WRITE_MEM_MODE:
            if (static_cast<uchar>(ba[i]) == 0xb3)
                emit writeErrorMsg(tr("Ошибка контр. суммы"));
            else if (static_cast<uchar>(ba[i]) == 0xb2)
                emit writeOKMsg(tr("Операция завершена"));
            else
                emit writeErrorMsg(tr("Ошибка: пришли непонятные данные"));

            break;


        }
    }




}
//         if ( isNenormDet ) {
//             tmpA.append(s[i]);
//             cnt++;
//             baTemp = tmpA;
//             baTemp = baTemp.toHex().toUpper();
//             if ((cmpFunc(baTemp, noNormOEM, cnt) == -1) && (cmpFunc(baTemp, noNormANSI, cnt) == -1)) {
//                 cnt=0;
//                 isNenormDet=false;
//                 outBA+=tmpA;
//                 tmpA.clear();
//                 continue;
//             } else {
//                 if (cnt==7) {
//                     emit signalNoNormReceived();
//                     emit signalReadyToShow(outBA);
//                     emit signalReadyToShowRed(tmpA);
//                     cnt=0;
//                     isNenormDet=false;
//                     tmpA.clear();
//                     outBA.clear();
//                 }
//                 continue;
//             }

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

//         else if (flWaitNoNorm && !isNenormDet) {
//             if (((unsigned char)s[i] == 0x8d)  || ((unsigned char)s[i] == 0xCD))  {
//                 isNenormDet = true;
//                 tmpA.append(s[i]);
//                 bigNindex=i;
//                 cnt++;
//                 continue;
//             }
//         }

//         if (msgStart) {
//             //первая 0F получена
//             tmpA.append(s[i]);
//             cnt++;
//             if (isKredo && (cnt == 4)) {
//                 retV = checkBArray(tmpA, KREDO_ANS);
//                 if (retV == 0) {
//                     if (ConvertMode == "OEM") {
//                         codec = QTextCodec::codecForName("cp866");
//                         modWaitMsg = codec->fromUnicode(msgKredoWait);
//                     }
//                     emit signalInsertInQueue(modWaitMsg);
//                     emit signalStopAllOperations("b4");
//                     tmpA.clear();
//                     cnt=0;
//                     msgStart=false;

//                 }
//             }
//             if (cnt==8) {
//                 if (detectFl) {
//                     //режим определения кода модуля
//                     retV = checkBArray(tmpA, DETECT_MODE);
//                     if (retV == 0) {
//                         //обычный модуль
//                         emit signalCodeDetect( tmpA  );
//                         emit signalWriteAnswerCode(tmpA);
//                         emit signalStopKredoMode();
//                     }
//                     else if (retV == 2) {
//                         //КРЕДО_3VS
//                         emit signalSetKredoMode();
//                         emit signalCodeDetect( tmpA );
//                         emit signalWriteAnswerCode("KREDO");
//                     }
//                     else {
//                         outBA += tmpA;
//                     }
//                 }else {
//                     //обычный режим
//                     retV = checkBArray(tmpA, SIMPLE_MODE);
//                     if (retV == 0) {
//                         //обычный модуль
//                         emit signalWriteAnswerCode(tmpA);
//                         emit signalStopKredoMode();
//                     }
//                     else if (retV == 2) {
//                         emit signalSetKredoMode();
//                         emit signalWriteAnswerCode("KREDO");

//                     }
//                     else {
//                         outBA += tmpA;
//                     }
//                 }
//                 tmpA.clear();
//                 cnt=0;
//                 msgStart=false;
//             }
//         }
//         else if ((s[i] == 0xF) && !msgStart) {
//             tmpA.append(s[i]);
//             cnt++;
//             msgStart=true;
//         }
//         else if (((unsigned char)s[i] == 0xb4) && !msgAnswRes){
//             msgAnswRes = true;
//             tmpA.append(s[i]);
//             cnt++;
//         }
//         else if (msgAnswRes) {
//             //получили от модуля ответ, что всё ок
//             tmpA.append(s[i]);
//             cnt++;
//             if (cnt == 5) {
//                 if (!checkBArray(tmpA, B4_MODE)) {
//                     codec = QTextCodec::codecForName("cp1251");
//                     modWaitMsg = codec->fromUnicode(msgKredoWait);
//                     emit signalInsertInQueue(modWaitMsg);
//                     emit signalStopAllOperations("b4");
//                 }else {
//                     outBA += tmpA;
//                 }
//                 tmpA.clear();
//                 cnt=0;
//                 msgAnswRes=false;
//             }
//         }
//         else {
//             outBA.append(s[i]);
//         }
//     }
//     emit signalReadyToShow(outBA);
//     outBA.clear();





