#include "mainwindow.h"




#include <QAbstractScrollArea>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), ini_file(QApplication::applicationDirPath() + "/MonServ.ini"),
      m_serial(new QSerialPort(this)), fl(nullptr), main_state(State::SimpleOutput) {

    ui->setupUi(this);

    init_comboBoxes();
    init_statusBar();
    restoreSettings();
    createCmdMem();


    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::manageSerialPort);
    connect(m_serial, &QSerialPort::errorOccurred, this, &MainWindow::handleErrorFromPort);
    connect(m_serial, &QSerialPort::readyRead, this, &MainWindow::readData);





    connect(ui->comboBox_3,  static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this, &MainWindow::slotReWrSettingsInIni);
    connect(ui->comboBox_4,  static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this, &MainWindow::slotReWrSettingsInIni);
    connect(ui->comboBox_5,  static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this, &MainWindow::slotReWrSettingsInIni);
    connect(ui->comboBox_6,  static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this, &MainWindow::slotReWrSettingsInIni);
    connect(ui->comboBox_7,  static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this, &MainWindow::slotReWrSettingsInIni);
    connect(ui->comboBox_8,  static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this, &MainWindow::slotReWrSettingsInIni);
    connect(ui->comboBox_9,  static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this, &MainWindow::slotReWrSettingsInIni);
    connect(ui->comboBox_10,  static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this, &MainWindow::slotReWrSettingsInIni);



    connect(ui->lineEdit, &QLineEdit::textChanged, this, [this, str = ui->lineEdit->text() ](){ setValueToIniFile("WorkingDirectories", "Reports_path", str);} );
    connect(ui->lineEdit_2, &QLineEdit::textChanged, this, [this, str = ui->lineEdit_2->text()]{ setValueToIniFile("WorkingDirectories", "Capture_path", str);} );
//  connect(action_3, &QAction::triggered, [this]() {ui->lineEdit_2->text( QDir::currentPath());
//                ui->lineEdit_1->text( QDir::currentPath());});
    connect(ui->checkBox_10, &QCheckBox::clicked, this,  [this] {ui->checkBox_10->isChecked() ? ui->lineEdit_18->setEnabled(true) : ui->lineEdit_18->setEnabled(false); });


     connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::slotSetWrkFilesDir);
     connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::slotSetWrkFilesDir);
     connect(ui->action_5, &QAction::triggered, this, &MainWindow::openButtonClicked);
     connect(ui->comboBox_8,  static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged), this, &MainWindow::showScript);


//     connect(ui->action_14, &QAction::triggered, this, )

     connect(ui->action_18, &QAction::triggered, this, &MainWindow::showMemForm);
     connect(ui->action_19, &QAction::triggered, this, &MainWindow::showPortForm);

     portForm = nullptr;
     memForm = nullptr;




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

void MainWindow::portOpReadData() {
    bool opRes;
    quint32 addr = ui_mem->lineEdit_10->text().toUInt(&opRes, 16);
    int size = 1;
    switch (ui_mem->comboBox_12->currentIndex()) {
        case 0:
            size = 1;
            break;
        case 1:
            size = 2;
            break;
        case 2:
            size = 4;
            break;
        case 3:
            size = 8;
            break;
    }
    operation_size = size;
    main_state = State::ReadPort;
//   monOperations *op = new monOperations(this, main_state, addr, size);
//    connect(op, &monOperations::signalWriteArrayToPort, this, &MainWindow::writeData );
//    op->begin_operation();


}


void MainWindow::memOpReadData() {
    bool opRes;
    quint32 addr = ui_mem->lineEdit_5->text().toUInt(&opRes, 16);
    int size = 1;
    monOperations *op;
    if (ui_mem->checkBox_3->isChecked()) {
        opInfo.opState = State::ReadFile;
        opInfo.opFile = ui_mem->lineEdit_13->text();
        //open file and clean it, then close again
        QFile fl(opInfo.opFile);
        fl.open(QIODevice::WriteOnly | QIODevice::Truncate);
        fl.close();
        size = ui_mem->lineEdit_8->text().toInt();
        op = new monOperations(this, opInfo, addr, size);

    }
    else {
        opInfo.opState = State::ReadMem;
        switch (ui_mem->comboBox_15->currentIndex()) {
            case 0:
                size = 1;
                break;
            case 1:
                size = 2;
                break;
            case 2:
                size = 4;
                break;
            case 3:
                size = 8;
                break;
        }
        op = new monOperations(this, opInfo, addr, size);
    }
    operation_size = size; //for del
    opInfo.opSize = size;
    connect(op, &monOperations::signalWriteArrayToPort, this, &MainWindow::writeData );
    op->begin_operation();
}

void MainWindow::memOpWriteData() {
    if (ui_mem->lineEdit_10->text().isEmpty()) {
        printRdData("err", tr("Не введен адрес"));
        return;
    }
    if (ui_mem->lineEdit_4->text().isEmpty()) {
        printRdData("err", tr("Не введены данные для записи"));
        return;
    }
    bool opRes;
    quint32 addr = ui_mem->lineEdit_10->text().toUInt(&opRes, 16);
    quint32 data = ui_mem->lineEdit_4->text().toUInt(&opRes, 16);
    int size = 1;
    switch (ui_mem->comboBox_12->currentIndex()) {
        case 0:
            size = 1;
            break;
        case 1:
            size = 2;
            break;
        case 2:
            size = 4;
            break;
        case 3:
            size = 8;
            break;
    }
    int repTimes = 1;
    bool needInfo = false;
    if (ui_mem->checkBox_6->isChecked()) {
        repTimes = ui_mem->lineEdit_7->text().toInt();
        needInfo = true;
    }

    while( repTimes ) {
        if (needInfo) {
            printRdData("info", QString::number(repTimes));
        }
        ui->textEdit->insertPlainText(QString::number(repTimes));
        operation_size = size;
        main_state = State::WriteMem;
  /*      monOperations *op = new monOperations(this, main_state, addr, size, data);
        connect(op, &monOperations::signalWriteArrayToPort, this, &MainWindow::writeData );
        op->begin_operation();*/
        repTimes--;
    }



    if (needInfo) {
        printRdData("info", tr("Операция завершена"));
    }

}

void MainWindow::showMemForm() {
    ui_mem = new Ui_Form_Mem;
    memForm = new QWidget;
    ui_mem->setupUi(memForm);
    memForm->show();
    ui_mem->pushButton_7->setEnabled(false);
    QString str = nullptr;
    getValueFromIni( PANEL_MEM_OP, WRITE_ADDR, str );
    ui_mem->lineEdit_5->setText(str);
    getValueFromIni( PANEL_MEM_OP, READ_ADDR, str );
    ui_mem->lineEdit_10->setText(str);
    getValueFromIni(PANEL_MEM_OP, WRITE_SIZE, str );
    ui_mem->comboBox_15->setCurrentText(str);
    getValueFromIni(PANEL_MEM_OP, READ_SIZE, str );
    ui_mem->comboBox_12->setCurrentText(str);
    getValueFromIni(PANEL_MEM_OP, JUMP_ADDR, str );
    ui_mem->lineEdit_20->setText(str);
    connect(ui_mem->pushButton_7, &QPushButton::clicked, this, &MainWindow::selectFileMemOp );
    connect(ui_mem->pushButton_18, &QPushButton::clicked, this, &MainWindow::memOpReadData );
    connect(ui_mem->pushButton_19, &QPushButton::clicked, this, &MainWindow::memOpWriteData );
    connect(ui_mem->checkBox_3, &QCheckBox::toggled, this, [&](bool bVal){ui_mem->pushButton_7->setEnabled(bVal); } );
    connect(ui_mem->comboBox_15,  static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this, &MainWindow::slotReWrSettingsInIni);
    connect(ui_mem->comboBox_12,  static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this, &MainWindow::slotReWrSettingsInIni);
    connect(ui_mem->lineEdit_5, &QLineEdit::editingFinished, this, [&]{ setValueToIniFile(PANEL_MEM_OP, WRITE_ADDR,  ui_mem->lineEdit_5->text());} );
    connect(ui_mem->lineEdit_10, &QLineEdit::editingFinished, this, [&]{ setValueToIniFile(PANEL_MEM_OP, READ_ADDR, ui_mem->lineEdit_10->text());} );
    connect(ui_mem->lineEdit_20, &QLineEdit::editingFinished, this, [&]{ setValueToIniFile(PANEL_MEM_OP, JUMP_ADDR, ui_mem->lineEdit_20->text());} );
    connect(ui_mem->checkBox_6, &QCheckBox::toggled, this, [&]( bool bV ){ if (bV) ui_mem->lineEdit_7->setFocus(); } );
}


void MainWindow::selectFileMemOp() {
    QString dir = "", pref = "";
    getValueFromIni( WorkingDirectories, LoadFileToMemory_path, dir );
    getValueFromIni("WorkingDirectories", "Prefix", pref );
    QString filename = QFileDialog::getOpenFileName(0, "OpenDialog", dir.isEmpty() ? QDir::currentPath() : dir,
                           pref.isEmpty() ? "Data files(*.bin);;COM files(*.com);;All files(*.*)" : pref  );
    if (!filename.isEmpty()) {
        setValueToIniFile(WorkingDirectories, LoadFileToMemory_path, QFileInfo(filename).path());
        ui_mem->lineEdit_13->setText(filename);      
        ui_mem->lineEdit_8->setText( QString::number(QFileInfo(filename).size()));
   //     memLoadFile flMem(filename);
   //     connect(&flMem, &memLoadFile::showMemFileSize, this, []() { qDebug() << "val"/*ui_mem->lineEdit_8->setText(QString::number(val))*/;} );
    }



}




void MainWindow::showPortForm() {
    ui_port = new Ui_Form_Port;
    portForm = new QWidget;
    ui_port->setupUi(portForm);
    portForm->show();

}


void MainWindow::createToolBars() {
  ui->toolBar->addAction(new QAction(tr("Очистить экран"), this));
  QLabel *lbl = new QLabel("aaaaaaaa");
  ui->toolBar->addWidget(lbl);

}

void MainWindow::addLineToTable(const QVector<QVector<QString>> &lines) {
    ui->tableWidget_2->setRowCount(lines.size());
    for (int i=0; i<lines.size(); ++i) {
        for (int j=0; j<4; ++j) {
            QTableWidgetItem *item = new QTableWidgetItem(lines.at(i).at(j));
            ui->tableWidget_2->setItem(i, j, item);
       }
    }
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode( 2, QHeaderView::Stretch);
}

void MainWindow::showScript(const QString &filename) {
    QList<QString>names;
    for (int i = 0; i < ui->comboBox_8->count(); ++i) {
         names.push_back(ui->comboBox_8->itemText(i));
    }
    int ind = names.indexOf(filename);
    qDebug() << ind;
    if ((ind != -1) && (ind)) {
        names.swap(0, ind);
    //    ui->comboBox_8->clear();
     //   ui->comboBox_8->addItems(names);
    }
    else {
 //       ui->comboBox_8->insertItem(0, filename);
    }
  //  ui->comboBox_8->setCurrentIndex(0);
    qDebug() << "\n Here!\n";

    DbgClass openS(filename, mCmd);
    tableLines = openS.showTable();
    addLineToTable(tableLines);
}

void MainWindow::openButtonClicked() {
    QString filename = QFileDialog::getOpenFileName(0, "OpenDialog", QDir::currentPath(), "*.dbg");
    if (!filename.isEmpty()){
        showScript(filename);
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


void MainWindow::printRdData(const QString &marker, const QString &data) {
    ui_mem->label_4->clear();
    if (marker == "mr") {
        ui_mem->lineEdit_12->clear();
        ui_mem->lineEdit_12->setText(data);
    }
    else if (marker == "err"  || marker == "info") {
        ui_mem->label_4->setStyleSheet(QString("font-size: %1px").arg(12));
        ui_mem->label_4->setText(data);
    }
    else if (marker == "pr") {
        ui_mem->lineEdit_4->setText(data);
    }
}


void MainWindow::readData() {
    const QByteArray data = m_serial->readAll();
    parseData p(this, data, &opInfo, operation_size );
    connect(&p, &parseData::showData, this, &MainWindow::showString);
    connect(&p, &parseData::printDataInField, this, &MainWindow::printRdData);
    p.parser();
}

void MainWindow::writeData(const QByteArray &data) {
    m_serial->write(data);
}


void MainWindow::showString( const QString &str ) {
    ui->textEdit->insertPlainText(str);
}

void MainWindow::manageSerialPort() {
    if ( ui->pushButton->text() == tr("Подключиться")) {
        openSerialPort();
    }
    else {
        closeSerialPort();
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (memForm) delete memForm;
    if (portForm) delete portForm;
}



MainWindow::~MainWindow() {
    closeSerialPort();
    saveSettings();
    delete ui;
}

void MainWindow::openSerialPort() {
   if (!ui->comboBox_3->currentText().isEmpty())
       m_serial->setPortName( ui->comboBox_3->currentText() );
   else {
       QMessageBox::critical(this, tr("Ошибка подключения"),
            tr("Не указан номер COM-порта"));
       return;
   }


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
void MainWindow::slotWriteComboToIni(const QString &keyName, QComboBox *cmb) {
    ini_file.remove(keyName);
    int sz = cmb->count();
    ini_file.beginWriteArray(keyName);
    QStringList lst;
    for (int i = 0; i < sz; ++i) {
        lst<<cmb->itemText(i);
    }
    lst=lst.toSet().toList();
    int  i = 0;
    for (const auto  &str : lst ) {
        ini_file.setArrayIndex(i);
        ini_file.setValue("name", lst.at(i));
        i++;
    }
    ini_file.endArray();
    ini_file.sync();
}

void MainWindow::slotReadFromIniToCombo(QComboBox *cmb) {
    QString keyNm;
    if (cmb == ui->comboBox) keyNm = MODNAME_KEY;
    else if (cmb == ui->comboBox_2) keyNm = MODNMBS_KEY;
    else if (cmb == ui->comboBox_11) keyNm = STNDNAME_KEY;
    else if (cmb == ui->comboBox_8) keyNm = SKRPTNAME_KEY;
    int sz=ini_file.beginReadArray(keyNm);
    for (int i=0; i<sz; ++i) {
        ini_file.setArrayIndex(i);
        cmb->addItem(ini_file.value("name").toString());
    }
    ini_file.endArray();
    if (sz) {
        int currInd = 0;
        getValueFromIni(INDX_KEY, keyNm, currInd );
        if (currInd <= sz ) cmb->setCurrentIndex(currInd);
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
    slotWriteComboToIni(SKRPTNAME_KEY, ui->comboBox_8);
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
     //список сценариев
     slotReadFromIniToCombo(ui->comboBox_8);
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
    qDebug() << "rewrite settings" << str.at(0);
    if (QObject::sender() == ui->comboBox_6) {
         setValueToIniFile("Settings", "COM_parity", str);
     }
     else if (QObject::sender() == ui->comboBox_7) {
         setValueToIniFile("Settings", "COM_stopBits", str);
     }
     else if (QObject::sender() == ui->comboBox_5) {
         setValueToIniFile("Settings", "COM_dataBits", str);
     }
     else if (QObject::sender() == ui->comboBox_4) {
         setValueToIniFile("Settings", "Com_speed", str);
     }
     else if (QObject::sender() == ui->comboBox_10) {
        setValueToIniFile("Settings", "Module_capacity", str);
        setValidatorsFunc(ui->comboBox_10);
    }
    else if (QObject::sender() == ui->comboBox_9) {
        setValueToIniFile("Settings", "Module_arch", str);
    }
    else if (QObject::sender() == ui->comboBox_3) {
        setValueToIniFile("Settings", "Com_index", str);
    }
    else if (QObject::sender() == ui_mem->comboBox_12) {
        setValueToIniFile(PANEL_MEM_OP, READ_SIZE, str);
    }
    else if (QObject::sender() == ui_mem->comboBox_15) {
        setValueToIniFile(PANEL_MEM_OP, WRITE_SIZE, str);
    }
}

void MainWindow::setValidatorsFunc(const QObject *var) {
    QRegExp rx;
    if (var == (QComboBox *)ui->comboBox_10) {
        QString tmpS;
        int cntResz=8;
        if (ui->comboBox_10->currentText() == "32 bits") {
            rx = QRegExp("[0-9a-fA-F]{8}");
//            ui->radioButton_9->setEnabled(false);
//            ui->radioButton_16->setEnabled(false);
            cntResz=8;
        }
        else {
            rx = QRegExp("[0-9a-fA-F]{16}");
//            ui->radioButton_9->setEnabled(true);
//            ui->radioButton_16->setEnabled(true);
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
    qDebug() << group << " " << section << " " << value << endl;
    ini_file.endGroup();
}


void MainWindow::setValueToIniFile( const QString &group, const QString &section, const QString &value ) {
    ini_file.beginGroup(group);
    ini_file.setValue(section, value);
    qDebug() << group << " " << section << " " << value << endl;
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


