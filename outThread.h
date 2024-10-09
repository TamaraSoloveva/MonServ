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
    Q_PARSER_CLASS( QMutex *m, QQueue<QByteArray>* q, QVector<QString> *cmdVec ) ;
    ~Q_PARSER_CLASS();

public slots:
    void process();

signals:
    void finished();
    void parseInputArray( const QByteArray &ba);
private slots:
    void slotParseInputArray( const QByteArray &ba );
private:
    QMutex *mutex;
    QQueue<QByteArray>* outputQ;
    QVector<QString> *cmdCodes;

};

#endif // OUTTHREAD_H
