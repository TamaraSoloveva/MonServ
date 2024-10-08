#ifndef OUTTHREAD_H
#define OUTTHREAD_H

#include <QThread>
#include <QQueue>
#include <QMutex>
#include <QMutexLocker>


// Пример реализации класса
class Q_PARSER_CLASS : public QObject {
    Q_OBJECT

public:
    Q_PARSER_CLASS( QMutex *m, QQueue<QByteArray>* q )  ;
    ~Q_PARSER_CLASS();

public slots:
    void process();

signals:
    void finished();

private:
    QMutex *mutex;
    QQueue<QByteArray>* outputQ;

};

#endif // OUTTHREAD_H
