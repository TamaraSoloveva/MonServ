#ifndef MEMLOADFILE_H
#define MEMLOADFILE_H

#include <QObject>
#include "common.h"

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
