#include "outThread.h"
#include <QDebug>
// Реализации методов класса


Q_PARSER_CLASS::Q_PARSER_CLASS(QMutex *m, QQueue<QByteArray> *q) : mutex(m), outputQ(q) {
  qDebug() << "run!";
}

Q_PARSER_CLASS::~Q_PARSER_CLASS() {
 }

void Q_PARSER_CLASS::process() {
     emit finished();
}



