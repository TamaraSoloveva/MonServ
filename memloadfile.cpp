#include "memloadfile.h"


MemotyOperationsTab::MemotyOperationsTab( const QString &txt1, const int &sz ) : size(sz), addr(txt1)  {
//    if (txt1.isEmpty())


}


MemotyOperationsTab::MemotyOperationsTab( const QString &txt1,  const QString &txt2, const int &sz ) : size(sz),
                                                    addr(txt1), data(txt2) {

}

MemotyOperationsTab::MemotyOperationsTab(const int &sz , HexSpinBox *hs, Debug_Operations_Class2 &dbgIn) : size(sz),
                            hspin(hs), dbg(&dbgIn) { }

MemotyOperationsTab::MemotyOperationsTab(const int &sz,  HexSpinBox *hspin, const QString sDt, Debug_Operations_Class2 &dbgIn ) :
                           size(sz), hspin(hspin), data(sDt), dbg(&dbgIn){}



void MemotyOperationsTab::checkAddress() {
    emit setAllEditsReady();
    if ( hspin->text().isEmpty() ) {
        emit errorNoData(hspin);
        return;
    }
    addrH = hspin->text().toUInt(&ok, 16);
}


void MemotyOperationsTab::runOperation() {
    checkAddress();
    getCmdType();
    sendInformationAboutOp();
    packDataAndSend();


}

//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------

void MemoryOP::getCmdType() {
     ( size == 1 ) ? cmdType = READ_MEM_BYTE : ( size == 2 ) ? cmdType = READ_MEM_WORD : cmdType = READ_MEM_DWORD;
}

void MemoryOP::sendInformationAboutOp() {
    QString str1(tr("Чтение из памяти 0x%1").arg(hspin->text()));
    emit sendMessage_log(str1);
    emit sendMessage_report(str1);
    emit sendMessage_status(tr("Чтение из памяти.."));
}

void MemoryOP::packDataAndSend() {
    dbg->MemRead(READ_MEM_MODE, addrH, cmdType);
}

//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
void WriteOPMem::getWriteData() {
    if (data.isEmpty())
        Dt = 0x0;
    else {
        bool ok;
        Dt = data.toUInt(&ok, 16);
    }



}

void WriteOPMem::getCmdType() {
    ( size == 1 ) ? cmdType = WRITE_MEM_BYTE : ( size == 2 ) ? cmdType = WRITE_MEM_WORD : cmdType = WRITE_MEM_DWORD;
    getWriteData();
}

void WriteOPMem::sendInformationAboutOp() {
    QString str1(tr("Запись данных 0x%1 по адресу 0x%2").arg(data).arg(hspin->text()));
    emit sendMessage_log(str1);
    emit sendMessage_report(str1);
    emit sendMessage_status(tr("Запись данных в память.."));
}

void WriteOPMem::packDataAndSend() {

    dbg->MemWrite(WRITE_MEM_MODE, addrH, Dt, size, cmdType );


}

//------------------------------------------------------------------------------------------------------------------










//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
memLoadFile::memLoadFile( QString flName) : filename(flName) {
    qFl = new QFile(filename);
    qFl->open( QIODevice::ReadOnly);
    if (qFl->isOpen()) {
        getFileSize();
    }
}

void memLoadFile::getFileSize() {
    const int flSz = qFl->size();
    emit showMemFileSize(flSz);
}
