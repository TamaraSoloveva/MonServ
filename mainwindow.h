#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include "parseData.h"
#include "script.h"

#include <QDebug>
#include <QSplitter>
#include <QToolBar>
#include <QDateTime>
#include <QQueue>
#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include <QInputDialog>


#include "ui_MonServ.h"
#include "ui_memWrRd.h"
#include "ui_portWrRd.h"
#include "common.h"
#include "memloadfile.h"



#include "monOperations.h"
#include "extLineEdit.h"
#include "report.h"
#include "hexspinbox.h"

#include "baseCommandClass.h"
#include "outThread.h"

#include "WorkingStrings.h"
#include "common.h"
#include "Work_variables.h"
#include "wrInfoClass.h"
#include "outputConsole.h"

#define STATUS_BAR_CONNECTION_INFO      0
#define STATUS_BAR_CONNECT_TIMER        1

struct MonQModes_t {
    bool detectMonCode; //режим определения ID-посылки модуля
    bool isKREDO;       //определён модуль КРЕДО-3VS
    bool isCodeDet;     //начат набор посылки-идент модуля
    bool isAckMsg;      //посылка модуль в ожидании команды
    bool isPSImode;     //выбор режима работы программы
    bool isUseLog;      //используем или нет log-файл
    bool isNewBios;     //тип BIOS
    bool isThreadRun;
    int modCode;
};




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class Ui_MainWindow;
class Script;
class Ui_Form_Mem;
class Ui_Form_Port;
class Report;

class ConTimer;
class Console;
class Q_PARSER_CLASS;

class Debug_Operations_Class;
class MemotyOperationsTab;

#define CONNECT_MSG                 "Подключиться"
#define DISCONNECT_MSG              "Отключиться"
#define CONNECT_MSG_STATUS_BAR      "Подключено"
#define DISCONNECT_MSG_STATUS_BAR   "Отключено"


class MainWindow : public QMainWindow, public Ui_MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     void print_message( const unsigned int &type, char *fmt, ...);
     Report *report_file;
     QVector<QByteArray>cmdCodes;
     QVector<QByteArray>cmdCodes_hex;
protected:
    void closeEvent(QCloseEvent *event) override;
    HexSpinBox *spinBox_1, *spinBox_2, *spinBox_3;
    Console *m_console;

    MemotyOperationsTab *op;

    std::unique_ptr<MemotyOperationsTab>op2;


    quint32 getOperationSize();

    QAction *codesWriteToIni, *codeAddToIni;

private:
    Ui::MainWindow *ui;
    QWidget *memForm, *portForm;
    Ui_Form_Mem *ui_mem;
    Ui_Form_Port *ui_port;
    QSplitter *h1Splitter, *h2Splitter;
    QSettings ini_file;
    QSerialPort *m_serial = nullptr;
    QVector<QLineEdit *>lineEdVect;
    QLibrary *libUSB;
    QVector<QVector<QString>>tableLines;
    Script *fl;
    useFields info;
    QMap<QString, useFields> mCmd;
    QQueue<QByteArray>qqq;

    QString connectMsg;

    wrInfoClass *wrInfoOb;

    QAction *actUtf8CodecSet, *actWinCodecSet;


    Debug_Operations_Class dbg;

    Debug_Operations_Class2 dbg2;

    QThread* thread;
    Q_PARSER_CLASS *parser;
    QMutex mutex;



    std::string GetReportName();

    MonQModes_t status_struct;
    //QTimer *timer_connection;
    // void countConnectionTime();
    //unsigned int hours, mins, secs;
    ConTimer *timer_connection;

    void init_statusVariables();

//    void WriteToStatus( const QString &msg ) {
//        if (!status_struct.isPSImode) {
//            ui->label_46->setVisible(true);
//            ui->label_46->setText(msg);
//        }
//    }

    QVector<QByteArray> convertCode( const QVector<QByteArray> &codes );



    operationInfo opInfo;
    State main_state;
    int operation_size;


    void createToolBars();
    QToolBar *scriptToolBar;

    //for memory operations
    extLineEdit *lineEdit_7, *lineEdit_8, *lineEdit_5, *lineEdit_12, *lineEdit_10, *lineEdit_4;

    qint8 openSerialPort();
    void closeSerialPort();

    void readData();
    void connectInterface( bool setConnected );
    int LoadUSBLib(const QString & libName);
    void createCmdMem();

    void init_comboBoxes();
    void init_statusBar();
    void restoreSettings();
    void saveSettings();
    void updateComInfo(  QComboBox *cb);
    void sortAlphabetically(QComboBox *cB);
    void setValidatorsFunc(const QObject *var);

    void getValueFromIni(const QString &group, const QString &section, int &value );
    void getValueFromIni(const QString &group, const QString &section, bool &value);
    void getValueFromIni(const QString &group, const QString &section, QString &value);
    void getValueFromIni(const QString &group, const QString &section, QByteArray &value);

    void setCodecs();


    typedef bool (*Toggle_Func_Type)( bool state );
    Toggle_Func_Type Toggle_Func;
    typedef int (*rele_on_type)( int num );
    rele_on_type rele_on;
    typedef int (*rele_off_type )( int num );
    rele_off_type rele_off;
    typedef int (*GetDeviceCount_type)();
    GetDeviceCount_type GetDeviceCount;
    typedef int (*rele_id_on_type) (int id);
    rele_id_on_type rele_id_on;
    typedef int (*rele_id_off_type) (int id);
    rele_id_off_type rele_id_off;
    typedef int (*rele_get_id_type)(int num);
    rele_get_id_type rele_get_id;
    typedef void (*free_mem_type)();
    free_mem_type free_mem;

private slots:
    void slotReWrSettingsInIni( const QString & str );
    void manageSerialPort();
    void handleErrorFromPort(QSerialPort::SerialPortError error);
    void slotSetWrkFilesDir();
    void slotReadFromIniToCombo(QComboBox *cmb);
    void slotWriteComboToIni(const QString &keyName, QComboBox *cmb);
    void selectFileMemOp();

    void setValueToIniFile( const QString &group, const QString &section, const QString &val );
    void setValueToIniFile( const QString &group, const QString &section, const bool &val );
    void setValueToIniFile( const QString &group, const QString &section, const int &val );
    void setValueToIniFile( const QString &group, const QString &section, const QByteArray &val );
    void writeOldCodeNumbersToIni();
    void addNewCodeNumberToIni();

    void openButtonClicked();
    void showScript(const QString &filename);
    void slotCancelButtonPushed();


    void memOpReadData();
    void memOpWriteData();
    void portOpReadData();

    void setReadAddr(const QString &str) { setValueToIniFile(WORK_PARAMS, MEM_READ_ED, str); }
    void setWriteAddr(const QString &str) { setValueToIniFile(WORK_PARAMS,MEM_WRITE_ED, str); }
    void setJumpAddr(const QString &str) { setValueToIniFile(WORK_PARAMS, MEM_JUMP_ED, str); }

    void changeEnableMode( bool setTrue );

    void slotChoosePathRprtCapture();

    void slotChangeOutputCodec();

    void noDataInAddressField( HexSpinBox *hb );
    void outReadData( const QByteArray &rdData, bool isMem );

    //вкладка "ОТЛАДЧИК"
    void slotMemOpCheckBox(bool ch);
    void slotReadButtonPushed();
    void slotWriteButtonPushed();


    void repaintBorderLines(QLineEdit *lineEd, bool isError);






public slots:
    void showString( const QString &str);
    void addLineToTable(const QVector<QVector<QString> > &line);
    void printRdData(const QString &marker, const QString &data);
    //out data to StatusBar
    void slotShowStatusBarInfo(const QString &msg );
    //switch Modes
    void slotSwitchMode(bool checked);

    void writeData(const QByteArray &data);
    //!!!!!!!!!!!!!!!!!!!!!!!!
    void slotAddDataToQueue ( const QByteArray &ba);
    void slotShowDataToConsole( const QByteArray &ba );

     void paintStartInterface();

     //функцуии выводаотладочной информации
     void slotShowMessageInfo( const QString &msg );
     void WriteToLOG( const QString &msg ) {}
     void WriteToStatus( const QString &msg ) {
         if (!status_struct.isPSImode) {
             ui->label_46->setVisible(true);
             ui->label_46->setText(msg);
         }
     }

     void WriteToReport(const QString &msg ) {}


     void showStatusOkMSG(const QString &msg);
     void showStatusErrMSG(const QString &msg);
signals:
    void signalSendMessageToEdit( const QString &msg );
    void signalSendMessageToStatusBar( const QString &msg );
    void signalSendDataArray( const QByteArray &arr );
    void signalSendMessageToOpStatus( const QString &msg  );
    void stopCurrentOperation();





};





#endif // MAINWINDOW_H
