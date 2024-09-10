#include "extLineEdit.h"

extLineEdit::extLineEdit(int mode, int l, int w, QWidget *parent) :
    mode(mode), length(l), width(w), QLineEdit(parent) {
    this->setFixedSize(width, length);
    switch (mode) {
    case 1:
        //numbers and space only
        this->setValidator(new QRegExpValidator(QRegExp("[0-9]{9}$")));
        break;
    }

}

void extLineEdit::slotTextChanged() {
//   QString str = this->text();
//   str = removeSpaces() ;
//   qDebug() << str;
//   switch(mode) {
//   case 1:
//       //000 000 000
//       if (str.length() > 3)
//           str.insert(str.length()-3, ' ');
//       if (str.length() > 7)
//           str.insert(str.length()-7, ' ');
//       break;
//   }
//   this->setText(str);
}

QString extLineEdit::removeSpaces() {
    QString str = this->text().simplified();
    str.replace( " ", "" );
    return str;
}

void extLineEdit::setRedFont() {
    this->setStyleSheet("color:red;");

}

void extLineEdit::setOkFont() {
    this->setStyleSheet("color:black;");

}

void extLineEdit::setRedBorders() {
    this->setStyleSheet("font-size: 10pt;  border-style: outset; border-width: 2px; border-color: #ff5500");
}

void extLineEdit::setOkBorders() {
    this->setStyleSheet("font-size: 12pt;  border-top-color: ##a2a2a2; border-width: 1px; border-color: #e7e7e7");
}
