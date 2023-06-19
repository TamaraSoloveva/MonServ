#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), ini_file(QApplication::applicationDirPath() + "/MonServ.ini")
{
    ui->setupUi(this);
    init_comboBoxes();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::init_comboBoxes() {
    QString str;
    getValueFromIni("Settings", "Com_index", str);
    updateComInfo( ui->comboBox_3 );
    sortAlphabetically(ui->comboBox_3);

//       if (!str.isEmpty()) ui->comboBox_3->setCurrentText(str);

//       getValueFromIni("Settings", "index_RFID", str);
//       UpdateComInfo( ui->comboBox_8 );
//       sortAlphabetically(ui->comboBox_8);
//       if (!str.isEmpty()) ui->comboBox_8->setCurrentText(str);

//       lst_speed << "921600" << "460800" << "230400"  << "115200" <<  "57600" <<"38400" <<"19200" <<"9600" << "4800";
//       ui->comboBox_4->addItems(lst_speed);
//       ui->comboBox_4->setMaxVisibleItems(4);
//       str = getStringFromIniFile("Settings", "Com_speed");
//       if (!str.isEmpty()) ui->comboBox_4->setCurrentText(str);

//       data_bits << "5" << "6" << "7" << "8";
//       ui->comboBox_5->addItems(data_bits);
//       str = getStringFromIniFile("Settings", "COM_dataBits");
//       if (!str.isEmpty()) ui->comboBox_5->setCurrentText(str);

//       par_lst << "No" << "Even" << "Odd";
//       ui->comboBox_6->addItems(par_lst);
//       str = getStringFromIniFile("Settings", "COM_parity");
//       if (!str.isEmpty()) ui->comboBox_6->setCurrentText(str);

//       stop_bits << "1" << "1,5" << "2";
//       ui->comboBox_7->addItems(stop_bits);
//       str = getStringFromIniFile("Settings", "COM_stopBits");
//       if (!str.isEmpty()) ui->comboBox_7->setCurrentText(str);

//       arch_list << "x86" << "Power PC" << "MIPS" <<"ARM" << "DSP" << "NIOS";
//       ui->comboBox_9->addItems(arch_list);
//       str = getStringFromIniFile("Settings", "Module_arch");
//       sortAlphabetically(ui->comboBox_9);
//       if (!str.isEmpty()) ui->comboBox_9->setCurrentText(str);

//       cap_list << "32 bits"  << "64 bits";
//       ui->comboBox_10->addItems(cap_list);
//       str = getStringFromIniFile("Settings", "Module_capacity");
//       if (!str.isEmpty()) ui->comboBox_10->setCurrentText(str);

       connect(ui->comboBox_6, SIGNAL(currentIndexChanged(QString)), SLOT(slotReWrSettingsInIni(QString)));
       connect(ui->comboBox_8, SIGNAL(currentIndexChanged(QString)), SLOT(slotReWrSettingsInIni(QString)));
       connect(ui->comboBox_7, SIGNAL(currentIndexChanged(QString)), SLOT(slotReWrSettingsInIni(QString)));
       connect(ui->comboBox_5, SIGNAL(currentIndexChanged(QString)), SLOT(slotReWrSettingsInIni(QString)));
       connect(ui->comboBox_4, SIGNAL(currentIndexChanged(QString)), SLOT(slotReWrSettingsInIni(QString)));
       connect(ui->comboBox_10, SIGNAL(currentIndexChanged(QString)),SLOT(slotReWrSettingsInIni(QString)));
       connect(ui->comboBox_9, SIGNAL(currentIndexChanged(QString)), SLOT(slotReWrSettingsInIni(QString)));
       connect(ui->comboBox_3, SIGNAL(currentIndexChanged(QString)), SLOT(slotReWrSettingsInIni(QString)));

       connect(ui->comboBox, SIGNAL(activated(QString)), SLOT(slotComboTextChanged()));
       connect(ui->comboBox_2, SIGNAL(activated(QString)), SLOT(slotComboTextChanged()));


}

void MainWindow::updateComInfo(QComboBox *cb) {
    cb->clear();
    int ind=0;
    const auto serialPortInfoList = QSerialPortInfo::availablePorts();
    //CHECK_IT work in Linux, dont work in WIN
#ifdef Q_OS_UNIX
    for (const QSerialPortInfo &serialPortInfoList : serialPortInfoList)
        obj->addItem(serialPortInfoList.portName());
#elif defined Q_OS_WIN32
    if (serialPortInfoList.count() !=  0) {
        QList<QSerialPortInfo>::const_iterator itr;
        itr = serialPortInfoList.begin();
        while (itr != serialPortInfoList.end()) {
            cb->insertItem(ind, (*itr).portName()  );
            ind++;
            itr++;
        }
    }
 #endif
}

void MainWindow::sortAlphabetically(QComboBox *cB) {
    QStringList tst;
    tst << "bbb" << "aaa";
    cB->addItems(tst);
    QStringList lst;
    const int count = cB->count();
    if (count > 2) {
        for (int i=count-1; i != -1; --i) {
            lst << cB->itemText(i);
            cB->removeItem(i);
        }
        lst.sort();
        cB->addItems(lst);
    }
}

void MainWindow::getValueFromIni( const QString &group, const QString &section, int &value )  {
    ini_file.beginGroup(group);
    value = ini_file.value(section, -1).toInt();
    ini_file.endGroup();
}

void MainWindow::getValueFromIni( const QString & group, const QString &section, bool &value )  {
    ini_file.beginGroup(group);
    value = ini_file.value(section, true).toBool();
    ini_file.endGroup();
}

void MainWindow::getValueFromIni( const QString & group, const QString &section, QString &value ) {
    ini_file.beginGroup(group);
    value = ini_file.value(section, "").toString();
    ini_file.endGroup();
}


void MainWindow::setValueToIniFile( const QString &group, const QString &section, const QString &value ) {
    ini_file.beginGroup(group);
    ini_file.setValue(section, value);
    ini_file.endGroup();
}

void MainWindow::setValueToIniFile( const QString &group, const QString &section, const int &value ) {
    ini_file.beginGroup(group);
    ini_file.setValue(section, value);
    ini_file.endGroup();
}

void MainWindow::setValueToIniFile(  const QString &group, const QString &section, const bool &value ) {
    ini_file.beginGroup(group);
    ini_file.setValue(section, value);
    ini_file.endGroup();
}


