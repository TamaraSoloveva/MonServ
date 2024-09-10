#include "parseData.h"
#include <cstring>


void parseData::parser() {
    sData = QString(data);
    QString resultStr = nullptr;
    int getVal = 0;
    quint16 chSm_cnt = 0, chSm_get = 0;
    unsigned char *arr1;




/* здесь в будущем будут разбираться входные данные в зависимости от режима работы, пока
 * режим только один State::SimpleOut
*/
  //  qDebug() << "callReadData*" << data.size() << data << data.at(0) << data.toHex();
    switch (op->opState) {
    case State::Empty:
        break;
    case State::SimpleOutput:
        resultStr = sData;
        emit showData(resultStr);
        break;
    case State::ReadMem:
    case State::ReadPort:
        if ( data.size() != 7){
            emit printDataInField("err", QString(tr("Ошибка при чтении данных")));
        }
        else {
            std::memcpy(inPack.arr, data.constData(), data.size());
            for (int i = 0; i < data.size() - 3; ++i) {
               chSm_cnt += inPack.arr[i];
            }
            chSm_get = inPack.arr[5];
            chSm_get <<= 8;
            chSm_get |= inPack.arr[4];
            if ( chSm_cnt != chSm_get) {
                emit printDataInField("err", QString(tr("Ошибка контрольной суммы")));
            }
            else {
                if (inPack.arr[6] != 0xb2) {
                    emit printDataInField("err",  QString(tr("Операция завершена с ошибкой")));
                }
                else {
                    switch (opSize) {
                    case 1:
                        resultStr =  QString::number(inPack.rdm.dt_rd.dt8, 16).rightJustified(2, '0');
                        break;
                    case 2:
                        resultStr =  QString::number(inPack.rdm.dt_rd.dt16, 16).rightJustified(4, '0');
                        break;
                    case 4:
                        resultStr =  QString::number(inPack.rdm.dt_rd.dt32, 16).rightJustified(8, '0');
                        break;
                    case 8:
                        resultStr =  QString::number(inPack.rdm.dt_rd.dt32, 16).rightJustified(8, '0');
                        break;
                    }
                    if ( op->opState == State::ReadPort )
                        emit printDataInField("pr", QString(resultStr));
                    else
                        emit printDataInField("mr", QString(resultStr));
                }
            }
        }

            break;
    case State::WriteMem:
        std::memcpy(inPack.arr, data.constData(), data.size());
        if (inPack.arr[0] != 0xb2)
            emit printDataInField("err",  QString(tr("Ошибка контрольной суммы")));
            break;
    case State::WritePort:
            break;
    case State::ReadFile:
    {
        std::unique_ptr<unsigned char[]> arr(new unsigned char[data.size()]);
        std::memcpy(arr.get(), data.constData(), data.size());
//        qDebug() << data.size();
        if (arr[0] == 0xb3)
            emit printDataInField("err",  QString(tr("Ошибка контрольной суммы")));
        else {
            QFile fl(op->opFile);
            if (!fl.open(QIODevice::WriteOnly|QIODevice::Append)){
                emit printDataInField("err",  QString(tr("Ошибка открытия файла")));
                return;
            }
            op->wrkSz += data.size();
            int max_v = 0;
            if ( op->wrkSz == op->opSize + 3) {
                max_v = data.size()-3;
                emit printDataInField("info", QString("Прочитано %1 байтов").arg(op->wrkSz - 3));
            }
            else {
                max_v = data.size();
                emit printDataInField("info", QString("Прочитано %1 байтов").arg(op->wrkSz));
            }

            for (int i = 0; i < max_v; ++i) {
                op->fileChSm += arr[i];
            }


            if ( op->wrkSz == op->opSize + 3) {
                fl.write(data, data.size()-3);
                chSm_get = arr[data.size()-2];
                chSm_get <<= 8;
                chSm_get |= arr[data.size()-3];
                if(chSm_get !=  op->fileChSm) {
                    emit printDataInField("err",  QString(tr("Ошибка приёма данных")));
                    return;
                }
                if (arr[data.size()-1] != 0xb2 ) {
                    emit printDataInField("err",  QString(tr("Ошибка приёма данных(b2)")));
                    return;
                }
                emit printDataInField("err",  QString(tr("Операция завершена")));
            }
            else
                fl.write(data, data.size());
            fl.flush();
            fl.close();
        }
    }
        break;
    case State::WriteFile:
        break;
    case State::Jump:
        break;
    }
}
