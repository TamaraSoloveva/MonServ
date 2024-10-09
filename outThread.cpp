#include "outThread.h"
#include <QDebug>
// Реализации методов класса


Q_PARSER_CLASS::Q_PARSER_CLASS(QMutex *m, QQueue<QByteArray> *q, QVector<QString> *cmdVec) : mutex(m),
                                        outputQ(q), cmdCodes(cmdVec) {

  connect( this, &Q_PARSER_CLASS::parseInputArray, this, &Q_PARSER_CLASS::slotParseInputArray );
}

Q_PARSER_CLASS::~Q_PARSER_CLASS() {
 }

void Q_PARSER_CLASS::process() {
    QByteArray ba;
    while (1) {
        if (!outputQ->isEmpty()) {
            QMutexLocker lock(mutex);
            while (!outputQ->isEmpty() )
            {
                ba+= outputQ->dequeue();
                emit parseInputArray(ba);
            }
        }
        else {

        }


    }



 //    emit finished();
}


void Q_PARSER_CLASS::slotParseInputArray( const QByteArray &ba ) {
    QByteArray outData;
    for (auto ch : ba ) {
      /*  if ( ch == '0xF') {

        }*/
        int a = 0;




    }
}



