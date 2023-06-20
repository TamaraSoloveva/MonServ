#include "mainwindow.h"

#include <QAbstractScrollArea>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), ini_file(QApplication::applicationDirPath() + "/MonServ.ini"),
      m_serial(new QSerialPort(this)) {

    ui->setupUi(this);
    init_comboBoxes();
    init_statusBar();
    restoreSettings();

    lineEdVect.append(ui->lineEdit_4);
    lineEdVect.append(ui->lineEdit_5);
    lineEdVect.append(ui->lineEdit_6);
    lineEdVect.append(ui->lineEdit_7);
    lineEdVect.append(ui->lineEdit_9);
    lineEdVect.append(ui->lineEdit_10);
    lineEdVect.append(ui->lineEdit_11);
    lineEdVect.append(ui->lineEdit_12);



    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::manageSerialPort);
    connect(m_serial, &QSerialPort::errorOccurred, this, &MainWindow::handleErrorFromPort);
    connect(m_serial, &QSerialPort::readyRead, this, &MainWindow::readData);

}

void MainWindow::handleErrorFromPort( QSerialPort::SerialPortError error) {
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), m_serial->errorString());
        closeSerialPort();
    }
}

void MainWindow::readData() {
    const QByteArray data = m_serial->readAll();
    parseData p(data);
    connect(&p, &parseData::showData, this, &MainWindow::showString);
    //connect(&p, &parseData::showData, ui->textEdit, &QTextEdit::insertPlainText);
    p.parser();
}

void MainWindow::showString( const QString &str ) {
    ui->textEdit->insertPlainText(str);

//    QScrollBar *bar = verticalScrollBar();
//    bar->setValue(bar->maximum());
}

void MainWindow::manageSerialPort() {
    if ( ui->pushButton->text() == "Подключиться") {
        openSerialPort();
    }
    else {
        closeSerialPort();
    }
}

MainWindow::~MainWindow() {
    saveSettings();
    delete ui;
}

void MainWindow::openSerialPort() {
    QString s  = ui->comboBox_3->currentText();
   if (!ui->comboBox_3->currentText().isEmpty())
       m_serial->setPortName( ui->comboBox_3->currentText() );
   else
       return;

   m_serial->setBaudRate( ui->comboBox_4->currentText().toInt());

   float stop_v = ui->comboBox_7->currentText().toFloat();
   if  (stop_v == 1)
        m_serial->setStopBits(QSerialPort::OneStop);
   else if (stop_v == 1.5)
       m_serial->setStopBits(QSerialPort::OneAndHalfStop);
   else if (stop_v == 2)
       m_serial->setStopBits(QSerialPort::TwoStop);
   else
       m_serial->setStopBits(QSerialPort::OneStop);

   QString par_str = ui->comboBox_6->currentText();
   if (par_str == "No")
        m_serial->setParity( QSerialPort::NoParity);
   else if (par_str == "Even")
       m_serial->setParity (QSerialPort::EvenParity);
   else if (par_str == "Odd")
       m_serial->setParity ( QSerialPort::OddParity);
   else m_serial->setParity( QSerialPort::NoParity);

   qint32 data_bits = ui->comboBox_5->currentText().toInt();
   if (data_bits == 5 )
       m_serial->setDataBits(QSerialPort::Data5);
   else if (data_bits == 6 )
           m_serial->setDataBits(QSerialPort::Data6);
   else if (data_bits == 7 )
           m_serial->setDataBits(QSerialPort::Data7);
   else if (data_bits == 8 )
           m_serial->setDataBits(QSerialPort::Data8);
   else
        m_serial->setDataBits(QSerialPort::Data8);

   m_serial->setFlowControl( QSerialPort::NoFlowControl);

   if (m_serial->open(QIODevice::ReadWrite)) {
        connectInterface(true);
   } else {
       QMessageBox::critical(this, tr("Error"), m_serial->errorString());

   }
}

void MainWindow::closeSerialPort() {
    if (m_serial->isOpen()) {
        m_serial->close();
        connectInterface(false);
    }

}


void MainWindow::saveSettings() {
    //сохранение положения на экране и размера
    setValueToIniFile("Settings", "GeometryX", MainWindow::geometry().x());
    setValueToIniFile("Settings", "GeometryY", MainWindow::geometry().y());
    setValueToIniFile("Settings", "Height", MainWindow::height());
    setValueToIniFile("Settings", "Width", MainWindow::width());
    ini_file.sync();
}


void MainWindow::restoreSettings() {
    //Восстанавливаем положение на экране + размеры
    QVector<int>params;
    int val;
    getValueFromIni("Settings", "GeometryX", val);
    params.push_back(val);
    getValueFromIni("Settings", "GeometryY", val),
    params.push_back(val);
    getValueFromIni("Settings", "Height", val);
    params.push_back(val);
    getValueFromIni("Settings", "Width", val);
    params.push_back(val);
    MainWindow::setGeometry( params.at(0), params.at(1), params.at(2), params.at(3));

    //В Windows 10 не прорисовываются кое-где границы
     if(QSysInfo::windowsVersion()==QSysInfo::WV_WINDOWS10){
            setStyleSheet(
                "QHeaderView::section{"
                    "border-top:0px solid #D8D8D8;"
                    "border-left:0px solid #D8D8D8;"
                    "border-right:1px solid #D8D8D8;"
                    "border-bottom: 1px solid #D8D8D8;"
                    "background-color:white;"
                    "padding:4px;"
                "}"
                "QTableCornerButton::section{"
                    "border-top:0px solid #D8D8D8;"
                    "border-left:0px solid #D8D8D8;"
                    "border-right:1px solid #D8D8D8;"
                    "border-bottom: 1px solid #D8D8D8;"
                    "background-color:white;"
                "}");
     }

}

void MainWindow::connectInterface( bool setConnected ) {
    if ( setConnected )
        ui->pushButton->setText((tr("Отключиться")));
    else
        ui->pushButton->setText((tr("Подключиться")));
    ui->comboBox_3->setEnabled(!setConnected);
    ui->comboBox_4->setEnabled(!setConnected);
    ui->comboBox_5->setEnabled(!setConnected);
    ui->comboBox_6->setEnabled(!setConnected);
    ui->comboBox_7->setEnabled(!setConnected);
    ui->comboBox_9->setEnabled(!setConnected);
    ui->comboBox_10->setEnabled(!setConnected);
    ui->pushButton_2->setEnabled(setConnected);
}

void MainWindow::init_statusBar() {
    QTimer *connectTimer = new QTimer(this);
   //connect(connectTimer, &QTimer::timeout, this, &MainWindow::)
    ui->statusbar->addWidget(new QLabel("00:00:00"));

}

void MainWindow::init_comboBoxes() {
    QString str;
    getValueFromIni("Settings", "Com_index", str);
    updateComInfo( ui->comboBox_3 );
    sortAlphabetically(ui->comboBox_3);
    if (!str.isEmpty()) ui->comboBox_3->setCurrentText(str);

    QStringList lst;
    lst << "921600" << "460800" << "230400"  << "115200" <<  "57600" <<"38400" <<"19200" <<"9600" << "4800";
    ui->comboBox_4->addItems(lst);
    ui->comboBox_4->setMaxVisibleItems(4);
    getValueFromIni("Settings", "Com_speed", str);
    if (!str.isEmpty()) ui->comboBox_4->setCurrentText(str);
    lst.clear();

    lst << "5" << "6" << "7" << "8";
    ui->comboBox_5->addItems(lst);
    getValueFromIni("Settings", "COM_dataBits", str);
    if (!str.isEmpty()) ui->comboBox_5->setCurrentText(str);
    lst.clear();

    lst << "No" << "Even" << "Odd";
    ui->comboBox_6->addItems(lst);
    getValueFromIni("Settings", "COM_parity", str);
    if (!str.isEmpty()) ui->comboBox_6->setCurrentText(str);
    lst.clear();

    lst<< "1" << "1,5" << "2";
    ui->comboBox_7->addItems(lst);
    getValueFromIni("Settings", "COM_stopBits", str);
    if (!str.isEmpty()) ui->comboBox_7->setCurrentText(str);
    lst.clear();

     lst << "x86" << "Power PC" << "MIPS" <<"ARM" << "DSP" << "NIOS";
     ui->comboBox_9->addItems(lst);
     getValueFromIni("Settings", "Module_arch", str);
     sortAlphabetically(ui->comboBox_9);
     if (!str.isEmpty()) ui->comboBox_9->setCurrentText(str);
     lst.clear();

     lst << "32 bits"  << "64 bits";
     ui->comboBox_10->addItems(lst);
     getValueFromIni("Settings", "Module_capacity", str);
     if (!str.isEmpty()) ui->comboBox_10->setCurrentText(str);

//   connect(ui->comboBox_6, SIGNAL(currentIndexChanged(QString)),  &MainWindow::slotReWrSettingsInIni );
//     connect(ui->comboBox_6, &QComboBox::currentIndexChanged, &MainWindow::slotReWrSettingsInIni);
//    connect(ui->comboBox_7, SIGNAL(currentIndexChanged(QString)), SLOT(slotReWrSettingsInIni(QString)));
//       connect(ui->comboBox_5, SIGNAL(currentIndexChanged(QString)), SLOT(slotReWrSettingsInIni(QString)));
//       connect(ui->comboBox_4, SIGNAL(currentIndexChanged(QString)), SLOT(slotReWrSettingsInIni(QString)));
//       connect(ui->comboBox_10, SIGNAL(currentIndexChanged(QString)),SLOT(slotReWrSettingsInIni(QString)));
//       connect(ui->comboBox_9, SIGNAL(currentIndexChanged(QString)), SLOT(slotReWrSettingsInIni(QString)));
//       connect(ui->comboBox_3, SIGNAL(currentIndexChanged(QString)), SLOT(slotReWrSettingsInIni(QString)));


////  connect(ui->comboBox)
//          connect(ui->comboBox, SIGNAL(activated(QString)), SLOT(slotComboTextChanged()));;
//       connect(ui->comboBox_2, SIGNAL(activated(QString)), SLOT(slotComboTextChanged()));
}


void MainWindow::slotReWrSettingsInIni( const QString & str ) {
    if (QObject::sender() == ui->comboBox_6) {
         setValueToIniFile("Settings", "COM_parity", str);
         //emit signalUpdateComParity(getComPortParity());
     }
     else if (QObject::sender() == ui->comboBox_7) {
         setValueToIniFile("Settings", "COM_stopBits", str);
         //emit signalUpdateComStopBits( getComStopBits());
     }
     else if (QObject::sender() == ui->comboBox_5) {
         setValueToIniFile("Settings", "COM_dataBits", str);
         //emit signalUpdateComDataBits(getComDataBits());
     }
     else if (QObject::sender() == ui->comboBox_4) {
         setValueToIniFile("Settings", "Com_speed", str);
        // emit signalUpdateComSpeed(ui->comboBox_4->currentText().toInt());
     }
     else if (QObject::sender() == ui->comboBox_10) {
        setValueToIniFile("Settings", "Module_capacity", str);
        setValidatorsFunc(ui->comboBox_10);
    }
    else if (QObject::sender() == ui->comboBox_9) setValueToIniFile("Settings", "Module_arch", str);
    else if (QObject::sender() == ui->comboBox_3) {
        setValueToIniFile("Settings", "Com_index", str);
       // emit signalUpdateComName(ui->comboBox_3->currentText());
    }
}

void MainWindow::setValidatorsFunc(const QObject *var) {
    QRegExp rx;
    if (var == (QComboBox *)ui->comboBox_10) {
        QString tmpS;
        int cntResz=8;
        if (ui->comboBox_10->currentText() == "32 bits") {
            rx = QRegExp("[0-9a-fA-F]{8}");
            ui->radioButton_9->setEnabled(false);
            ui->radioButton_16->setEnabled(false);
            cntResz=8;
        }
        else {
            rx = QRegExp("[0-9a-fA-F]{16}");
            ui->radioButton_9->setEnabled(true);
            ui->radioButton_16->setEnabled(true);
            cntResz=16;
        }
        QValidator *numbersOnly = new QRegExpValidator(rx, this);

        for (int i=0; i<lineEdVect.count(); ++i)
            lineEdVect.at(i)->setValidator(numbersOnly);

        if (cntResz == 8) {
            for (int i=0; i<lineEdVect.count(); i++) {
                tmpS = lineEdVect.at(i)->text();
                if (tmpS.length() > cntResz) {
                    tmpS.resize(cntResz);
                    lineEdVect.at(i)->clear();
                    lineEdVect.at(i)->setText(tmpS);
                }
            }
        }
    }
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
    QStringList lst;
    const int count = cB->count();
    if (count >= 2) {
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

void MainWindow::setValueToIniFile( const QString &group, const QString &section, const bool &value ) {
    ini_file.beginGroup(group);
    ini_file.setValue(section, value);
    ini_file.endGroup();
}


