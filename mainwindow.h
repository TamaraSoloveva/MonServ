#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include "parseData.h"
#include "script.h"

#include <QDebug>
#include <QSplitter>
#include <QToolBar>
#include "ui_MonServ.h"
#include "ui_memWrRd.h"
#include "ui_portWrRd.h"
#include "common.h"
#include "memloadfile.h"


#include "monOperations.h"




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class Ui_MainWindow;
class Script;
class Ui_Form_Mem;
class Ui_Form_Port;



class MainWindow : public QMainWindow, public Ui_MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void closeEvent(QCloseEvent *event) override;

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


    operationInfo opInfo;
    State main_state;
    int operation_size;


    void createToolBars();
    QToolBar *scriptToolBar;

    void openSerialPort();
    void closeSerialPort();
    void writeData(const QByteArray &data);
    void readData();
    void connectInterface( bool setConnected );
    int LoadUSBLib(const QString & libName);
    void createCmdMem();

    void init_comboBoxes();
    void init_statusBar();
    void restoreSettings();
    void saveSettings();
    void updateComInfo( QComboBox *cb);
    void sortAlphabetically(QComboBox *cB);
    void setValidatorsFunc(const QObject *var);

    void getValueFromIni(const QString &group, const QString &section, int &value);
    void getValueFromIni(const QString &group, const QString &section, bool &value);
    void getValueFromIni(const QString &group, const QString &section, QString &value);


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

    void openButtonClicked();
    void showScript(const QString &filename);

    void showMemForm();
    void showPortForm();

    void memOpReadData();
    void memOpWriteData();
    void portOpReadData();




public slots:
    void showString( const QString &str);
    void addLineToTable(const QVector<QVector<QString> > &line);
    void printRdData(const QString &marker, const QString &data);


signals:




};
#endif // MAINWINDOW_H
