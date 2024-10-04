#ifndef REPORT_H
#define REPORT_H

#include "textDocument.h"

class OpenDirectoryClass {
public:
    OpenDirectoryClass( const std::string & f_n );
    virtual ~OpenDirectoryClass(){};
};



class ConTimer : public QTimer {
    Q_OBJECT
    unsigned int secs, hours, mins;
    QString time_str;
public:
    ConTimer();
    ~ConTimer() = default;
    void resetTimer() { secs = hours = mins = 0 ;  time_str = "0:00:00" ; }
    void slotCountConnectionTime() ;

signals:
    emit void signalOutTimer( const QString &time_str );



};







#endif // REPORT_H
