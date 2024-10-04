#pragma once
#ifndef EXTLINEEDIT_H
#define EXTLINEEDIT_H
#include "common.h"
#include <QLineEdit>
#include <QRegExpValidator>

//mode = 1 - numbers in dec only

class extLineEdit : public QLineEdit {
    Q_OBJECT

 public:
    extLineEdit( int mode, int l, int w, QWidget *parent = 0 );
    virtual ~extLineEdit() = default;
    void setRedFont();
    void setRedBorders();
    void setOkFont();
    void setOkBorders();
    QString removeSpaces();


private:
    int mode;
    int length;
    int width;





signals:

public slots:
    void slotTextChanged();







};



#endif
