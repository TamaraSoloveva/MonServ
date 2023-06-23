#include "mainwindow.h"



#include <QAbstractScrollArea>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), ini_file(QApplication::applicationDirPath() + "/MonServ.ini"),
      m_serial(new QSerialPort(this)), fl(nullptr) {

    ui->setupUi(this);
    init_comboBoxes();
    init_statusBar();
    restoreSettings();
    createCmdMem();

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

    connect(ui->comboBox_6,  static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this, &MainWindow::slotReWrSettingsInIni);
    connect(ui->comboBox_8,  static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this, &MainWindow::slotReWrSettingsInIni);
    connect(ui->comboBox_7,  static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this, &MainWindow::slotReWrSettingsInIni);
    connect(ui->comboBox_5,  static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this, &MainWindow::slotReWrSettingsInIni);
    connect(ui->comboBox_4,  static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this, &MainWindow::slotReWrSettingsInIni);
    connect(ui->comboBox_10,  static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this, &MainWindow::slotReWrSettingsInIni);
    connect(ui->comboBox_9,  static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this, &MainWindow::slotReWrSettingsInIni);
    connect(ui->comboBox_3,  static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this, &MainWindow::slotReWrSettingsInIni);

    connect(ui->lineEdit, &QLineEdit::textChanged, [this, str = ui->lineEdit->text() ](){ setValueToIniFile("WorkingDirectories", "Reports_path", str);} );
    connect(ui->lineEdit_2, &QLineEdit::textChanged, [this, str = ui->lineEdit_2->text()]{ setValueToIniFile("WorkingDirectories", "Capture_path", str);} );
//    connect(action_3, &QAction::triggered, [this]() {ui->lineEdit_2->text( QDir::currentPath());
//                ui->lineEdit_1->text( QDir::currentPath());});


     connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::slotSetWrkFilesDir);
     connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::slotSetWrkFilesDir);
     connect(ui->pushButton_29, &QPushButton::clicked, this, &MainWindow::openButtonClicked);

    //Библиотека USB
//    int bLoad = LoadUSBLib( QDir::currentPath() + "/MP709.dll" );
//    if (bLoad == -1) {
//       QMessageBox::critical(0, "MonServ",
//              QString(tr("Библиотека MP709.dll не обнаружена в каталоге %1")).arg( QDir::currentPath().toUtf8().data()),
//              QMessageBox::Ok);
//    }
//    else if (bLoad == -2)
//        QMessageBox::critical(0, "MonServ", tr("Ошибка при подгрузке функций"), QMessageBox::Ok);

}

void MainWindow::addLineToTable(const QVector<QVector<QString>> &lines) {
    ui->tableWidget_2->setRowCount(lines.size());
    ui->tableWidget_2->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

    for (int i=0; i<lines.size(); ++i) {
        for (int j=0; j<4; ++j) {
            QTableWidgetItem *item = new QTableWidgetItem(lines.at(i).at(j));
            ui->tableWidget_2->setItem(i, j, item);
       }
    }
}

void MainWindow::openButtonClicked() {
    QString filename = QFileDialog::getOpenFileName(0, "OpenDialog", QDir::currentPath(), "*.dbg");
    if (!filename.isEmpty()){
        ui->comboBox_8->insertItem(0,filename);
        //RAII
        DbgClass openS(filename, mCmd);
        tableLines = openS.showTable();
        addLineToTable(tableLines);
    }

}

void MainWindow::createCmdMem() {
    mCmd.insert("j", useFields("Jump", 1, 0, 1));
    mCmd.insert("to", useFields("Text Out", 0, 0, 1));
    mCmd.insert("ja", useFields("Jump To Address", 1, 1, 1));
    mCmd.insert("cl", useFields("Call", 1, 0, 1));
    mCmd.insert("r", useFields("Ret", 0, 0, 1));
    mCmd.insert("lf", useFields("Load File", 1, 1, 1));
    mCmd.insert("mw", useFields("Memory Write", 1, 1, 1));


}

int MainWindow::LoadUSBLib(const QString & libName) {
    if (!QFile::exists(libName))
        return -1;
    libUSB  = new QLibrary(libName);
    libUSB->load();
    bool bLoaded = libUSB->isLoaded();
    if ( !bLoaded )
        return -2;
    Toggle_Func = (Toggle_Func_Type)libUSB->resolve("__Toggle");
    if (!Toggle_Func) return -2;
    rele_on = (rele_on_type)libUSB->resolve("_rele_on");
    if (!rele_on) return -2;
    rele_off = (rele_off_type)libUSB->resolve("_rele_off");
    if (!rele_off) return -2;
    GetDeviceCount = (GetDeviceCount_type)libUSB->resolve("_GetDeviceCount");
    if (!GetDeviceCount) return -2;
    rele_id_on = (rele_id_on_type)libUSB->resolve("_rele_id_on");
    if (!rele_id_on) return -2;
    rele_id_off = (rele_id_off_type)libUSB->resolve("_rele_id_off");
    if (!rele_id_off) return -2;
    rele_get_id = (rele_get_id_type)libUSB->resolve("_rele_get_id");
    if (!rele_get_id) return -2;
    free_mem = (free_mem_type)libUSB->resolve("_free_mem");
    if (!free_mem) return -2;
    return 0;
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
    p.parser();
}


void MainWindow::showString( const QString &str ) {
    ui->textEdit->insertPlainText(str);
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
   if (!ui->comboBox_3->currentText().isEmpty())
       m_serial->setPortName( ui->comboBox_3->currentText() );
   else
       throw std::invalid_argument("Input seral port name");

   if (ui->comboBox_4->currentText().isEmpty())
        throw std::invalid_argument("Input seral port baud rate");
   m_serial->setBaudRate( ui->comboBox_4->currentText().toInt());

   if ( ui->comboBox_7->currentText().isEmpty() )
       throw std::invalid_argument("Input seral port stop bits number");
   float stop_v = ui->comboBox_7->currentText().toFloat();
   if  (stop_v == 1)
        m_serial->setStopBits(QSerialPort::OneStop);
   else if (stop_v == 1.5)
       m_serial->setStopBits(QSerialPort::OneAndHalfStop);
   else if (stop_v == 2)
       m_serial->setStopBits(QSerialPort::TwoStop);
   else
       m_serial->setStopBits(QSerialPort::OneStop);

   if ( ui->comboBox_6->currentText().isEmpty() )
       throw std::invalid_argument("Input seral port stop parity");
   QString par_str = ui->comboBox_6->currentText();
   if (par_str == "No")
        m_serial->setParity( QSerialPort::NoParity);
   else if (par_str == "Even")
       m_serial->setParity (QSerialPort::EvenParity);
   else if (par_str == "Odd")
       m_serial->setParity ( QSerialPort::OddParity);
   else m_serial->setParity( QSerialPort::NoParity);

   if ( ui->comboBox_5->currentText().isEmpty() )
       throw std::invalid_argument("Input seral port data_bits");
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
    setValueToIniFile("WorkingDirectories", "Reports_path", ui->lineEdit->text());
    setValueToIniFile("WorkingDirectories", "Capture_path", ui->lineEdit_2->text());
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
    MainWindow::setGeometry( params.at(0), params.at(1), params.at(3), params.at(2));

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
     QString str = nullptr;
     getValueFromIni("WorkingDirectories", "Reports_path", str);
     ui->lineEdit->setText(str);
     getValueFromIni("WorkingDirectories", "Capture_path", str);
     ui->lineEdit_2->setText(str);


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
//    QTimer *connectTimer = new QTimer(this);
//   //connect(connectTimer, &QTimer::timeout, this, &MainWindow::)
//    ui->statusbar->addWidget(new QLabel("00:00:00"));

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
}

void MainWindow::slotSetWrkFilesDir() {
    QLineEdit *ed=nullptr;
    if (QObject::sender() == ui->pushButton_5) {
        ed = ui->lineEdit;
    } else if (QObject::sender() == ui->pushButton_6) {
        ed = ui->lineEdit_2;
    }
    QString dir = QFileDialog::getExistingDirectory(0, QString(tr("Выберите каталог")));
    if (ed) ed->setText( dir.isEmpty() ?  ed->text() : dir );
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
        delete numbersOnly;
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
    ini_file.sync();
}

void MainWindow::setValueToIniFile( const QString &group, const QString &section, const int &value ) {
    ini_file.beginGroup(group);
    ini_file.setValue(section, value);
    ini_file.endGroup();
    ini_file.sync();
}

void MainWindow::setValueToIniFile( const QString &group, const QString &section, const bool &value ) {
    ini_file.beginGroup(group);
    ini_file.setValue(section, value);
    ini_file.endGroup();
    ini_file.sync();
}


