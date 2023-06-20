#pragma once

#include <QObject>
#include <QByteArray>
#include <QString>


class parseData : public QObject  {
    Q_OBJECT
public:
    explicit parseData( const QByteArray & data ) : data(data), state(State::SimpleOutput) {};
    parseData(const parseData &other) = delete;
    parseData &operator=(const parseData &other) = delete;
    void parser();




private:
    enum class State {
        Empty,
        SimpleOutput,
        ReadMem,
        ReadPort,
        WriteMem,
        WritePort,
        Jump,
        WriteFile,
        ReadFile
     };
    QByteArray data;
    QString sData;
    State state;
signals:
    void showData( const QString &data);



};
