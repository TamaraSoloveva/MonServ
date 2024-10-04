#include "report.h"
#include "textDocument.h"

ConTimer::ConTimer() : secs(0), hours(0), mins(0) {}


void ConTimer::slotCountConnectionTime() {
    secs++;
    if ( secs > 60 ) {
        secs = 0;
        mins++;
        if (mins > 60) {
            mins = 0;
            hours++;
        }
    }
    time_str = QString(hours)+ ":" + QString(mins)+ ":" + QString(secs);
    emit signalOutTimer( time_str );
}

