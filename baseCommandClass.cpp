#include "baseCommandClass.h"
#include "common.h"

Debug_Operations_Class2::Debug_Operations_Class2() {

}

void Debug_Operations_Class2::MemRead(const int &OP_TYPE, const quint32 &Adr,  const int &type) {
    out_Mon out_data;
    int wrSz = sizeof (rqRDM);
    out_data.rdm.hdr.lbl1 = PACK_START;
    out_data.rdm.hdr.adr = Adr;
    out_data.rdm.hdr.lbl2 = type;
    unsigned int ChSm = 0, tmp1= 0;
    int sz = 0;
    sz = sizeof(rqRDM) - sizeof(ushort);
    for ( int i = 0; i < sz; ++i )
        ChSm += out_data.arr[i];

   tmp1 = ChSm;
   ChSm = (ChSm & 0x0000ff00) >>8;
   tmp1 =  (tmp1 & 0x000000ff) << 8 ;
   ChSm |= tmp1;
   out_data.rdm.ChSm = ChSm;
   emit signalSetOutputMode(OP_TYPE);
   emit signalWriteCapture( QString(reinterpret_cast<char *>(out_data.arr)) );
   emit signalWritePort( QByteArray::fromRawData(reinterpret_cast<const char *>(out_data.arr), wrSz) );
}

void Debug_Operations_Class2::MemWrite (const int &OP_TYPE, const quint32 &Adr, const quint32 &Dt, const int &Sz, const int &type ) {
    out_Mon out_data;
    int wrSz = sizeof (rqWRM);
    out_data.wrm.hdr.lbl1 = PACK_START;
    out_data.wrm.hdr.adr = Adr;
    out_data.wrm.hdr.lbl2 = type;
    Sz == 1 ? out_data.wrm.dt_w.dt8 = Dt : Sz == 2 ? out_data.wrm.dt_w.dt16 = Dt : out_data.wrm.dt_w.dt32 = Dt;

    unsigned int ChSm = 0, tmp1= 0;
    int sz = 0;
    sz = sizeof(rqWRM) - sizeof(ushort);
    for ( int i = 0; i < sz; ++i )
        ChSm += out_data.arr[i];

   tmp1 = ChSm;
   ChSm = (ChSm & 0x0000ff00) >>8;
   tmp1 =  (tmp1 & 0x000000ff) << 8 ;
   ChSm |= tmp1;
   out_data.wrm.ChSm = ChSm;
  qDebug() <<  QByteArray::fromRawData(reinterpret_cast<const char *>(out_data.arr), wrSz).toHex();
   emit signalSetOutputMode(OP_TYPE);
   emit signalWriteCapture( QString(reinterpret_cast<char *>(out_data.arr)) );
   emit signalWritePort( QByteArray::fromRawData(reinterpret_cast<const char *>(out_data.arr), wrSz) );
}



//-------------------------------------------------------------------------------------------------------

void Debug_Operations_Class::MemRead( const quint32 &Adr,  const int &type ) {
    out_Mon out_data;
    int wrSz = sizeof (rqRDM);
    out_data.rdm.hdr.lbl1 = PACK_START;
    out_data.rdm.hdr.adr = Adr;
    out_data.rdm.hdr.lbl2 = type;
    unsigned int ChSm = 0, tmp1= 0;
    int sz = 0;
    sz = sizeof(rqRDM) - sizeof(UN short);
    for ( int i = 0; i < sz; ++i )
        ChSm += out_data.arr[i];

   tmp1 = ChSm;
   ChSm = (ChSm & 0x0000ff00) >>8;
   tmp1 =  (tmp1 & 0x000000ff) << 8 ;
   ChSm |= tmp1;
   out_data.rdm.ChSm = ChSm;
   qDebug() <<  QByteArray::fromRawData(reinterpret_cast<const char *>(out_data.arr), wrSz).toHex();
   emit signalWriteCapture( QString(reinterpret_cast<char *>(out_data.arr)) );
   emit signalWritePort( QByteArray::fromRawData(reinterpret_cast<const char *>(out_data.arr), wrSz) );
}

void Debug_Operations_Class::IORead( const quint32 &Adr,  const int &type ) {
    out_Mon out_data;
    int wrSz = sizeof (rqRDM);
    out_data.rdm.hdr.lbl1 = PACK_START;
    out_data.rdm.hdr.adr = Adr;
    out_data.rdm.hdr.lbl2 = type;
    unsigned int ChSm = 0, tmp1= 0;
    int sz = 0;
    sz = sizeof(rqRDM) - sizeof(UN short);
    for ( int i = 0; i < sz; ++i )
        ChSm += out_data.arr[i];

   tmp1 = ChSm;
   ChSm = (ChSm & 0x0000ff00) >>8;
   tmp1 =  (tmp1 & 0x000000ff) << 8 ;
   ChSm |= tmp1;
   out_data.rdm.ChSm = ChSm;
   emit signalWriteCapture( QString(reinterpret_cast<char *>(out_data.arr)) );
   emit signalWritePort( QByteArray::fromRawData(reinterpret_cast<const char *>(out_data.arr), wrSz) );
}

void Debug_Operations_Class::MemReadToFile( const quint32 &Adr, const QString &filename, const int &Sz ) {


}

