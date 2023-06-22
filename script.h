#pragma once
#include <QObject>
#include <QTableWidget>
#include <iostream>
#include <fstream>
#include <QMultiMap>

struct useFields {
    useFields(const QString &str, bool use1, bool use2, bool use3) : fullName(str), addrField(use1),
        dataField(use2),commField(use3)  {}
    useFields() {}
    QString fullName;
    bool addrField;
    bool dataField;
    bool commField;
};

class Script : public QObject {
    Q_OBJECT
public:
    explicit Script(const QString & fl ) : dbgName(fl) {  createCmdMap(); fOpenButton(); }

public slots:
    void fOpenButton();


private:
    QString dbgName;
    QVector<QString>lineVec;
    QVector<QVector<QString>>v;

    useFields info;
    QMap<QString, useFields> mCmd;
    void createCmdMap();

    void formVector(const std::string &str);






signals:
    void addLine(const QVector<QVector<QString>> & line);



};
