#ifndef HEXSPINBOX_H
#define HEXSPINBOX_H

#include <QSpinBox>


class HexSpinBox : public QSpinBox
{
public:
    HexSpinBox(QWidget *parent = 0) : QSpinBox(parent) {
        setDisplayIntegerBase(16);
        setRange(INT_MIN, INT_MAX);
    }
    unsigned int hexValue() const {
        return u(value());
    }
    void setHexValue(unsigned int value) {
        setValue(i(value));
    }
protected:
    QString textFromValue(int value) const override {
        return QString::number(u(value), 16).toUpper();
    }
    int valueFromText(const QString &text) const override {
        if (text.size() != 0)
            return i(text.toUInt(0, 16));
    }
    QValidator::State validate(QString &input, int &pos) const override {
        if (input.size() == 0)
            return QValidator::Acceptable;
        QString copy(input);
        input = copy.toUpper();
        bool okay = false;
        unsigned int val = copy.toUInt(&okay, 16);
        if (!okay)
            return QValidator::Invalid;
        return QValidator::Acceptable;
    }

private:
    unsigned int u(int i) const {
        return *reinterpret_cast<unsigned int *>(&i);
    }
    int i(unsigned int u) const {
        return *reinterpret_cast<int *>(&u);
    }

};
#endif // HEXSPINBOX_H
