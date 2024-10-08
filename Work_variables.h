#ifndef WORK_VARIABLES_H
#define WORK_VARIABLES_H
#include <QtGlobal>

#define  RD_SZ 1024 //по 1kb данных вычитываем из com-порта

#define     MEM_KREDO_WR    0x500
#define     MEM_KREDO_WR_R  0x501
#define		MEM_WRITE_BYTE	0x51
#define		MEM_WRITE_WORD	0x52
#define		MEM_WRITE_DWORD	0x54
#define     MEM_WRITE_32    0x58


#define     GET_FL_FROM_MEM  0x35

//====== OpMode ====================
#define SET_SMPL_MODE 1
#define SET_RD_MODE 2
#define SET_WR_MODE 4
#define SET_PRT_RD_MODE 5
#define SET_PRT_WR_MODE 3
#define SET_JMP_MODE 6
#define SET_LDFILE_MODE 7
#define SET_RDFILE_MODE 8
#define SET_ERROR 95

#define SET_RD_MOD_SCRPT 20
//====== OpStat ====================
#define OpStat_UnDEf_RES 0 //непонятное значение, вариант ненормы протокола
#define OpStat_ERROR 95
#define OpStatWR_OK 5   //запись в память, i/o и jump
#define OpStatRD_OK 3   //чтение из памяти и i/o
#define OpStat_READY_BLOCK_WR 70
#define OpStatWrToFile_OK 7
#define OpStat_OutMon 1
#define OpStat_JumpOk 2
#define OpStat_JumpOkButWait 4
#define OpStat_RSErr    10
#define OpStat_ZAGErr    11
#define OpStat_ChSmErr    12
//======DateTime format
#define DDMMYYYY_TIMEDVOET 0
#define HHMMSS 1
#define YYYYMMDD 2


#define MODNAME_KEY "ModName"
#define MODNMBS_KEY "ModNumbers"
#define STNDNAME_KEY "StendName"
#define INDX_KEY "Indexes"
#define MOD_CODES "ModuleCodes"
#define MOD_CODES_FILED "code"
#define SKRPTNAME_KEY "ScriptList"


#define DETECT_MODE 0
#define SIMPLE_MODE 1
#define B4_MODE     2
#define KREDO_ANS   3

#define UN unsigned

#pragma pack(push, 1)


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


//====== структуры для отправки в COM порт ==========

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

typedef struct hdr_KredoVE_t                     //для КРЕДО-VS 07.08.14
{
    UN char marker[3]; 		//маркер заголовка "ZAG"
    UN long sz_f; 			//размер загружаемого модуля в байтах
    UN short offzag;      //смещение адреса загрузки
    UN short segzag;      //сегмент адреса загрузки
    UN short i_sp;        //значение sp перед запуском модуля
    UN short i_ss;        //значение ss перед запуском модуля
    UN short i_ip;        //значение ip перед запуском модуля
    UN short i_cs;        //значение cs перед запуском модуля
    UN char typ_start;  	//тип старта:
                            //0xF0 (загр. и запуск исп.кодов) или
                            //0xF2 (загр. данных или исп. кодов)
    UN char chk_summ;   	//контрольная сумма
    UN char mm[11];     	//массив, выравнивающий длину заголовка
                            //посылки до 2 параграфов

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

//====== структуры для получения ответа из COM порта =======
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

struct OpSettings {
    quint32 OpStat;          //финальный статус текущей операции
    quint32 OpMode;          //код операции, чтобы понять в потоке, результат на какую команду ждём
};

#pragma pack(pop)



#endif // WORK_VARIABLES_H
