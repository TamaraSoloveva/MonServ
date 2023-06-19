#pragma once

#include <QLabel>
#include <QTimer>
#include <QTime>

class showClock : public QLabel {
    Q_OBJECT

public:
        showClock( QWidget *obj = 0 );

private:
        QTimer *timer;
        quint32 sec, min, hours;
public slots:
        void changeTimeStr();
};
