#include "memloadfile.h"

memLoadFile::memLoadFile( QString flName) : filename(flName) {
    qFl = new QFile(filename);
    qFl->open( QIODevice::ReadOnly);
    if (qFl->isOpen()) {
        getFileSize();
    }
}

void memLoadFile::getFileSize() {
    const int flSz = qFl->size();
    emit showMemFileSize(flSz);
}
