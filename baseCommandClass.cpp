#include "baseCommandClass.h"
#include "common.h"



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
   emit signalWriteCapture( QString(reinterpret_cast<char *>(out_data.arr)) );
   emit signalWritePort( QByteArray::fromRawData(reinterpret_cast<const char *>(out_data.arr), wrSz) );
}

void Debug_Operations_Class::MemReadToFile( const quint32 &Adr, const QString &filename, const int &Sz ) {


}

