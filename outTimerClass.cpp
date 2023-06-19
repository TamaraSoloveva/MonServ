#include "outTimerClass.h"

showClock::showClock(QWidget *obj) : QLabel(obj) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &showClock::changeTimeStr);

}

void showClock::changeTimeStr() {

}
