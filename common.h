#pragma once

#include <QSettings>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QVector>
#include <QShortcut>
#include <QMessageBox>
#include <QTimer>
#include <QPlainTextEdit>
#include <QScrollBar>
#include <QDir>
#include <QLibrary>
#include <QFileDialog>
#include <QMultiMap>
#include <QString>
#include <QTableWidget>
#include <iostream>
#include <QFile>
#include <QDebug>
#include <QChar>
#include <QTextCodec>

struct useFields {
    useFields(const QString &str, bool use1, bool use2, bool use3) : fullName(str), addrField(use1),
        dataField(use2),commField(use3)  {}
    useFields() {}

    QString fullName;
    bool addrField;
    bool dataField;
    bool commField;
};

#define MODNAME_KEY "ModName"
#define MODNMBS_KEY "ModNumbers"
#define STNDNAME_KEY "StendName"
#define INDX_KEY "Indexes"
#define MOD_CODES "ModuleCodes"
#define MOD_CODES_FILED "code"
#define SKRPTNAME_KEY "ScriptList"
