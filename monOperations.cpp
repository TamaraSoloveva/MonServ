#include "monOperations.h"



void monOperations::begin_operation() {
    packData();
}

void monOperations::packData(){
    uint32_t ChSm = 0;
    int wrSz = 0, arraySz = 0;
    uint32_t tmp = 0;
    switch(opInfo.opState) {
    case State::Empty:
        break;
    case State::SimpleOutput:
        break;
    case State::ReadMem:
        wrSz = sizeof (rqRDM);
        outPack.rdm.hdr.lbl1 = PACK_START;
        outPack.rdm.hdr.adr = addr;
        if (size == 1)
            outPack.rdm.hdr.lbl2 = READ_MEM_BYTE;
        else if (size == 2)
            outPack.rdm.hdr.lbl2 = READ_MEM_WORD;
        else if (size == 4)
            outPack.rdm.hdr.lbl2 = READ_MEM_DWORD;
        arraySz = sizeof(rqRDM) - sizeof(UN short);
        for (int i = 0; i < arraySz; ++i)
            ChSm += outPack.arr[i];
        tmp = ChSm;
        ChSm = (ChSm & 0x0000ff00) >>8;
        tmp =  (tmp & 0x000000ff) << 8 ;
        ChSm |= tmp;
        outPack.rdm.ChSm = ChSm;
        break;
    case State::ReadPort:
        wrSz = sizeof (rqRDM);
        outPack.rdm.hdr.lbl1 = PACK_START;
        outPack.rdm.hdr.adr = addr;
        if (size == 1)
            outPack.rdm.hdr.lbl2 = READ_PORT_BYTE;
        else if (size == 2)
            outPack.rdm.hdr.lbl2 = READ_PORT_WORD;
        else if (size == 4)
            outPack.rdm.hdr.lbl2 = READ_PORT_DWORD;
        arraySz = sizeof(rqRDM) - sizeof(UN short);
        for (int i = 0; i < arraySz; ++i)
            ChSm += outPack.arr[i];
        tmp = ChSm;
        ChSm = (ChSm & 0x0000ff00) >>8;
        tmp =  (tmp & 0x000000ff) << 8 ;
        ChSm |= tmp;
        outPack.rdm.ChSm = ChSm;
        break;
    case State::WriteMem:
        wrSz = sizeof (rqWRM);
        outPack.wrm.hdr.lbl1 = PACK_START;
        outPack.wrm.hdr.adr = addr;
        if (size == 1) {
            outPack.wrm.hdr.lbl2 = WRITE_MEM_BYTE;
            outPack.wrm.dt_w.dt8 = (unsigned char)data;
        }
        else if (size == 2) {
            outPack.wrm.hdr.lbl2 = WRITE_MEM_WORD;
            outPack.wrm.dt_w.dt16 = (unsigned short)data;
        }
        else if (size == 4) {
            outPack.wrm.hdr.lbl2 = WRITE_MEM_DWORD;
            outPack.wrm.dt_w.dt32 = data;
        }
        arraySz = sizeof(rqWRM) - sizeof(UN short);
        for (int i = 0; i < arraySz; ++i)
            ChSm += outPack.arr[i];
        tmp = ChSm;
        ChSm = (ChSm & 0x0000ff00) >>8;
        tmp =  (tmp & 0x000000ff) << 8 ;
        ChSm |= tmp;
        outPack.wrm.ChSm = ChSm;
        break;

    case State::WritePort:
        break;
    case State::ReadFile:
        wrSz = sizeof (rqWRBM);
        outPack.wrbm.hdr.lbl1 = 0x31;
        outPack.wrbm.hdr.adr = addr;
        outPack.wrbm.hdr.lbl2 = READ_FILE_FROM_MEM;
        outPack.wrbm.num_b = size;
        arraySz = sizeof(rqWRBM) - sizeof(UN short);
        for (int i = 0; i < arraySz; ++i)
            ChSm += outPack.arr[i];
        tmp = ChSm;
        ChSm = (ChSm & 0x0000ff00) >>8;
        tmp =  (tmp & 0x000000ff) << 8 ;
        ChSm |= tmp;
        outPack.wrbm.ChSm = ChSm;
        break;
    case State::Jump:
        break;
    case State::WriteFile:




        break;

    }


    QByteArray array = QByteArray::fromRawData((const char *)outPack.arr, wrSz);
    emit signalWriteArrayToPort(array);
}



