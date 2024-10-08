#ifndef ARRPROT
#define ARRPROT

#define UN unsigned

#include "Work_variables.h"

#pragma pack(1)

/*
typedef union _Dt_t   //received data
{
   UN int 	dt32;   //double word
   UN short dt16;   //word
   UN char 	dt8;    //byte
}DT;


typedef struct _PH_t    //first 6 bytes of a protocol message
{
  UN char  lbl1;
  UN int   adr;
  UN char  lbl2;
}ProtHd;


typedef struct _rq_WRMEM_t           //write to memory
{
   ProtHd hdr;
   DT dt_w;
   UN short ChSm;
}rqWRM;

typedef struct _rq_RDMEM_t			//read from memory
{
   ProtHd hdr;
   UN short ChSm;
}rqRDM;

typedef struct _rq_RDBLKMEM_t
{
    ProtHd hdr;
    UN int num_b;
    UN short ChSm;
}rqRDBM;

typedef struct _rq_WRBLKMEM_t
{
    ProtHd hdr;
    UN int num_b;
    UN short ChSm;
}rqWRBM;

typedef struct _rq_JMPMEM_t
{
    ProtHd hdr;
    UN short ChSm;
}rqJMPM;

typedef struct hdr_KredoVE_t                     //РґР»СЏ РљР Р•Р”Рћ-VS 07.08.14
{
    UN char marker[3]; 		//РјР°СЂРєРµСЂ Р·Р°РіРѕР»РѕРІРєР° "ZAG"
    UN long sz_f; 			//СЂР°Р·РјРµСЂ Р·Р°РіСЂСѓР¶Р°РµРјРѕРіРѕ РјРѕРґСѓР»СЏ РІ Р±Р°Р№С‚Р°С…
    UN short offzag;      //СЃРјРµС‰РµРЅРёРµ Р°РґСЂРµСЃР° Р·Р°РіСЂСѓР·РєРё
    UN short segzag;      //СЃРµРіРјРµРЅС‚ Р°РґСЂРµСЃР° Р·Р°РіСЂСѓР·РєРё
    UN short i_sp;        //Р·РЅР°С‡РµРЅРёРµ sp РїРµСЂРµРґ Р·Р°РїСѓСЃРєРѕРј РјРѕРґСѓР»СЏ
    UN short i_ss;        //Р·РЅР°С‡РµРЅРёРµ ss РїРµСЂРµРґ Р·Р°РїСѓСЃРєРѕРј РјРѕРґСѓР»СЏ
    UN short i_ip;        //Р·РЅР°С‡РµРЅРёРµ ip РїРµСЂРµРґ Р·Р°РїСѓСЃРєРѕРј РјРѕРґСѓР»СЏ
    UN short i_cs;        //Р·РЅР°С‡РµРЅРёРµ cs РїРµСЂРµРґ Р·Р°РїСѓСЃРєРѕРј РјРѕРґСѓР»СЏ
    UN char typ_start;  	//С‚РёРї СЃС‚Р°СЂС‚Р°:
                            //0xF0 (Р·Р°РіСЂ. Рё Р·Р°РїСѓСЃРє РёСЃРї.РєРѕРґРѕРІ) РёР»Рё
                            //0xF2 (Р·Р°РіСЂ. РґР°РЅРЅС‹С… РёР»Рё РёСЃРї. РєРѕРґРѕРІ)
    UN char chk_summ;   	//РєРѕРЅС‚СЂРѕР»СЊРЅР°СЏ СЃСѓРјРјР°
    UN char mm[11];     	//РјР°СЃСЃРёРІ, РІС‹СЂР°РІРЅРёРІР°СЋС‰РёР№ РґР»РёРЅСѓ Р·Р°РіРѕР»РѕРІРєР°
                            //РїРѕСЃС‹Р»РєРё РґРѕ 2 РїР°СЂР°РіСЂР°С„РѕРІ

}rqWRHdrVS;

typedef union _rq_SNDC_t
{
  UN char arr[sizeof(rqWRM)];
  UN char arrb[sizeof(rqWRBM)];
  UN char arrvs[sizeof(rqWRHdrVS)];
  rqWRM wrm;
  rqRDM rdm;
  rqRDBM rdbm;
  rqWRBM wrbm;
  rqJMPM jmpm;
  rqWRHdrVS wrzag;
}out_Mon;

typedef struct _ans_RDMEM_t           //answer the read from memory command
{
   DT dt_rd;
   UN short ChSm;
   UN char ans;
}aRDM;


typedef union _rq_GTC_t
{
  UN char arr[sizeof(aRDM)];
  aRDM rdm;
}in_Mon;

//struct OpSettings {
//    UN int OpStat;          //С„РёРЅР°Р»СЊРЅС‹Р№ СЃС‚Р°С‚СѓСЃ С‚РµРєСѓС‰РµР№ РѕРїРµСЂР°С†РёРё
//    UN int OpCode;          //РєРѕРґ РѕРїРµСЂР°С†РёРё, С‡С‚РѕР±С‹ РїРѕРЅСЏС‚СЊ РІ РїРѕС‚РѕРєРµ, СЂРµР·СѓР»СЊС‚Р°С‚ РЅР° РєР°РєСѓСЋ РєРѕРјР°РЅРґСѓ Р¶РґС‘Рј
//};
*/
#pragma pack()

#endif // ARRPROT

