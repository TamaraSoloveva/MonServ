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
#include <memory>

#include "WorkingStrings.h"

struct useFields {
    useFields(const QString &str, bool use1, bool use2, bool use3) : fullName(str), addrField(use1),
        dataField(use2),commField(use3)  {}
    useFields() {}

    QString fullName;
    bool addrField;
    bool dataField;
    bool commField;
};


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

struct operationInfo {
    State opState = State::SimpleOutput;
    quint32 opSize = 0;
    QString opFile = "";
    quint16 fileChSm = 0;
    quint32 wrkSz = 0;
};

#define MODNAME_KEY     "ModName"
#define MODNMBS_KEY     "ModNumbers"
#define STNDNAME_KEY    "StendName"
#define INDX_KEY        "Indexes"
#define MOD_CODES       "ModuleCodes"
#define MOD_CODES_FILED "code"
#define SKRPTNAME_KEY   "ScriptList"

#define PANEL_MEM_OP    "Memory operations"
#define WRITE_ADDR      "Wr address"
#define READ_ADDR       "Rd address"
#define WRITE_SIZE      "Wr Size"
#define READ_SIZE       "Rd Size"
#define JUMP_ADDR       "Jmp addr"


const QString WorkingDirectories = WORK_DIRS;
const QString LoadFileToMemory_path = "LoadPath";


#define READ_MEM_MODE 2


const quint8 PACK_START = 0x31;
const quint8 READ_MEM_BYTE = 0x61;
const quint8 READ_MEM_WORD = 0x62;
const quint8 READ_MEM_DWORD = 0x64;
const quint8 WRITE_MEM_BYTE = 0x51;
const quint8 WRITE_MEM_WORD = 0x52;
const quint8 WRITE_MEM_DWORD = 0x54;

const quint8 READ_PORT_BYTE = 0x41;
const quint8 READ_PORT_WORD = 0x42;
const quint8 READ_PORT_DWORD = 0x44;

const quint8 LOAD_FILE_TO_MEM = 0x33;
const quint8 READ_FILE_FROM_MEM = 0x35;
const quint8 JUMP_TO_MEM = 0x38;

