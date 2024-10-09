#ifdef Q_OS_WIN32
#include <windows.h>
#else
//тут будут каки-то библиотеки для Unix
#endif

#include "mainwindow.h"
#include <QAbstractScrollArea>

#include <QDir>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_serial(new QSerialPort(this)),
      fl(nullptr), main_state(State::SimpleOutput) {
    ui->setupUi(this);
#ifdef Q_OS_WINDOWS
    ini_file.setPath(QSettings::NativeFormat, QSettings::UserScope, QApplication::applicationDirPath() + "/MonServ.ini");
#else
   ini_file.setPath(QSettings::NativeFormat, QSettings::UserScope, QApplication::applicationDirPath() + "/MonServ.conf" );
#endif

    spinBox_1 = new HexSpinBox;
    ui->gridLayout_8->addWidget(spinBox_1, 3, 0);
    spinBox_1->setMinimumWidth(171);
    spinBox_1->setMinimumHeight(27);
    QString addrStr;
    bool ok = true;
    getValueFromIni(WORK_PARAMS, MEM_READ_ED, addrStr);
    spinBox_1->setHexValue(addrStr.toUInt( &ok, 16));

    spinBox_2 = new HexSpinBox;
    ui->gridLayout_8->addWidget(spinBox_2, 3, 2);
    spinBox_2->setMinimumWidth(171);
    spinBox_2->setMinimumHeight(27);
    getValueFromIni(WORK_PARAMS, PORT_WRITE_ED, addrStr);
    spinBox_2->setHexValue(addrStr.toUInt( &ok, 16));

    spinBox_3 = new HexSpinBox;
    ui->gridLayout_8->addWidget(spinBox_3, 4, 2);
    spinBox_3->setMinimumWidth(171);
    spinBox_3->setMinimumHeight(27);
    getValueFromIni(WORK_PARAMS, MEM_JUMP_ED, addrStr);
    spinBox_2->setHexValue(addrStr.toUInt( &ok, 16));

    //Потом убрать в Creator !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    ui->textEdit_4->setEnabled(true);
    ui->textEdit_4->setReadOnly(false);
    ui->actionConnection->setCheckable(true);
    ui->action_25->setCheckable(true);
    ui->action_26->setCheckable(true);
    ui->statusBar->setVisible(true);
    ui->action_6->setEnabled(false);
    ui->action_7->setEnabled(false);
    ui->action_8->setEnabled(false);
    ui->label_46->setVisible(false);
    ui->textEdit->setVisible(false);

    //============================================================================
    init_statusVariables();

    init_comboBoxes();
    init_statusBar();
    restoreSettings();
    createCmdMem();

    bool checked = false;
    getValueFromIni(APP_INFO, ANSI_OUT, checked);
    ui->radioButton_4->setChecked(checked);
    getValueFromIni(APP_INFO, OEM_OUT, checked);
    ui->radioButton_5->setChecked(checked);
    getValueFromIni(APP_INFO, HEX_OUT, checked);
    ui->radioButton_6->setChecked(checked);

    codesWriteToIni = new QAction( tr("Записать коды модулей в ini-файл") );
    ui->menu_2->insertAction(ui->action_3, codesWriteToIni);

    setCodecs();

    thread = new QThread;
    parser = new Q_PARSER_CLASS(&mutex, &qqq, &cmdCodes );
    parser->moveToThread(thread);
    connect(thread, &QThread::started, parser, &Q_PARSER_CLASS::process);
    connect(parser, &Q_PARSER_CLASS::finished, thread, &QThread::quit );
    connect(parser, &Q_PARSER_CLASS::finished, parser,  &Q_PARSER_CLASS::deleteLater );
    connect(thread, &QThread::finished, thread,  &QThread::deleteLater);
    thread->start();


    //создаём экран для вывода данных
    m_console = new Console;
 //  m_console->setFont(font);
    m_console->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->verticalLayout->insertWidget(1, m_console );

    wrInfoOb = new wrInfoClass("OEM");

    //ЧТЕНИЕ ДАННЫХ ИЗ ПОРТА
    connect(m_serial, &QSerialPort::errorOccurred, this, &MainWindow::handleErrorFromPort);
    connect(m_serial, &QSerialPort::readyRead, this, &MainWindow::readData);

   //вывод данных на экран slotAddDataToQueue
   //connect( comPrt, SIGNAL(dataOutToConsole(QByteArray)), this, SLOT(slotAddDataToQueue(QByteArray)));
     connect( wrInfoOb, &wrInfoClass::signalInsertInQueue, this, &MainWindow::slotAddDataToQueue );
   //connect(comPrt, SIGNAL(convDataOutToConsole(QByteArray)), this, SLOT(slotConvDataOutToConsole(QByteArray)));
    connect (this, SIGNAL(signalSendDataArray(QByteArray)), wrInfoOb, SLOT(slotReceiveArray(QByteArray)));
    connect( wrInfoOb, SIGNAL(signalReadyToShow(QByteArray)), this, SLOT(slotShowDataToConsole(QByteArray)));




    connect(ui->actionConnection, &QAction::triggered, this, &MainWindow::manageSerialPort);
    connect(ui->action_5, &QAction::triggered, this, &MainWindow::openButtonClicked);

    connect(ui->comboBox_3,  static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this, &MainWindow::slotReWrSettingsInIni);
    connect(ui->comboBox_4,  static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this, &MainWindow::slotReWrSettingsInIni);
    connect(ui->comboBox_5,  static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this, &MainWindow::slotReWrSettingsInIni);
    connect(ui->comboBox_6,  static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this, &MainWindow::slotReWrSettingsInIni);
    connect(ui->comboBox_7,  static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
           this,  &MainWindow::slotReWrSettingsInIni);
    connect(ui->comboBox_8,  static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this, &MainWindow::slotReWrSettingsInIni);
    connect(ui->comboBox_9,  static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this, &MainWindow::slotReWrSettingsInIni);
    connect(ui->comboBox_10,  static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this, &MainWindow::slotReWrSettingsInIni);


    //system menu button - "Get default directories"
    connect(ui->action_3, &QAction::triggered, this, [this]() { ui->lineEdit_2->setText( QDir::currentPath());
                  ui->lineEdit->setText( QDir::currentPath()); setValueToIniFile(WORK_DIRS, RPRT_PATH,  QDir::currentPath());
                  setValueToIniFile(WORK_DIRS, CAPTURE_PATH,  QDir::currentPath());
                  emit signalSendMessageToEdit(QString(tr("Пути к рабочим файлам установлены по умолчанию"))); });


    connect(codesWriteToIni, &QAction::triggered, this, &MainWindow::writeOldCodeNumbersToIni );
    connect(ui->action_25, &QAction::triggered, this,  &MainWindow::slotSwitchMode);
//    connect(ui->action_25, &QAction::triggered, this, [=] (bool checked){ui->action_26->setChecked(!checked);} );
    connect(ui->action_26, &QAction::triggered, this,  &MainWindow::slotSwitchMode);
//    connect(ui->action_26, &QAction::triggered, this, [=] (bool checked){ui->action_25->setChecked(!checked);} );

    connect(ui->toolButton_2, &QToolButton::clicked, this, &MainWindow::slotChoosePathRprtCapture );
    connect(ui->toolButton_3, &QToolButton::clicked, this, &MainWindow::slotChoosePathRprtCapture );

    connect(this, &MainWindow::signalSendMessageToEdit, this, &MainWindow::slotShowMessageInfo );
    connect(this, &MainWindow::signalSendMessageToStatusBar, this, &MainWindow::slotShowStatusBarInfo );

    connect(ui->checkBox_2, &QCheckBox::clicked, this,[=](bool checked){ status_struct.isNewBios = checked;
        setValueToIniFile(MODULE_INFO, NEW_BIOS_CHECK, status_struct.isNewBios);} );
    connect(ui->checkBox_8, &QCheckBox::clicked, this, [=](bool checked){ui->lineEdit_7->setEnabled(checked);
                                                       ui->lineEdit_7->setFocus();} );

    connect(ui->checkBox_9, &QCheckBox::clicked, this, [=](bool checked){ui->lineEdit_10->setEnabled(checked);
                                                       ui->lineEdit_10->setFocus();} );

    connect(ui->lineEdit_8, &QLineEdit::textEdited, this, [=](QString txt ){ui->lineEdit_8->setText(txt.toUpper()); });
    connect(ui->lineEdit_9, &QLineEdit::textEdited, this, [=](QString txt ){ui->lineEdit_9->setText(txt.toUpper()); });
    connect(ui->lineEdit_14, &QLineEdit::textEdited, this, [=](QString txt ){ui->lineEdit_14->setText(txt.toUpper()); });

    //I/O fields
    ui->lineEdit_8->setValidator(new QRegExpValidator(QRegExp("[0-9A-Fa-f]{8}")));
    ui->lineEdit_9->setValidator(new QRegExpValidator(QRegExp("[0-9A-Fa-f]{8}")));
    ui->lineEdit_14->setValidator(new QRegExpValidator(QRegExp("[0-9A-Fa-f]{8}")));
    //Memory fields
    ui->lineEdit_7->setValidator(new QRegExpValidator(QRegExp("[0-9]{16}")));
    ui->lineEdit_10->setValidator(new QRegExpValidator(QRegExp("[0-9]{16}")));
    connect(ui->lineEdit_8, &QLineEdit::textChanged, this, [=]{ setValueToIniFile(WORK_PARAMS, PORT_READ_ED, ui->lineEdit_8->text());} );
    connect(ui->lineEdit_9, &QLineEdit::textChanged, this, [=]{ setValueToIniFile(WORK_PARAMS, PORT_WRITE_ED, ui->lineEdit_9->text());} );
    connect(spinBox_1, &HexSpinBox::textChanged, this, [=]{setValueToIniFile(WORK_PARAMS, MEM_READ_ED, QString(spinBox_1->hexValue())); });
    connect(spinBox_2, &HexSpinBox::textChanged, this, [=]{setValueToIniFile(WORK_PARAMS, MEM_WRITE_ED,QString(spinBox_2->hexValue())); });
    connect(spinBox_3, &HexSpinBox::textChanged, this, [=]{setValueToIniFile(WORK_PARAMS, MEM_JUMP_ED, QString(spinBox_3->hexValue()));  });

    ui->radioButton_4->setCheckable(true);
    connect(ui->radioButton_4, &QRadioButton::clicked, this, &MainWindow::slotChangeOutputCodec);
    connect(ui->radioButton_5, &QRadioButton::clicked, this, &MainWindow::slotChangeOutputCodec);
    connect(ui->radioButton_6, &QRadioButton::clicked, this, &MainWindow::slotChangeOutputCodec);

    //ВКЛАДКА "ОТЛАДКА"
    //нажатие галочки "Использовать файл"
    connect( ui->checkBox_9, &QCheckBox::clicked, this, &MainWindow::slotMemOpCheckBox );
    //считать
    connect (ui->pushButton_10, &QPushButton::clicked, this, &MainWindow::slotReadButtonPushed );
    //отправить
    connect (ui->pushButton_11, SIGNAL(clicked()), this, SLOT(slotWriteButtonPushed()));
    //считать из порта
    connect (ui->pushButton_4, SIGNAL(clicked()), this, SLOT(slotReadPrtButtonPushed()));
    //отправить в порт
    connect (ui->pushButton_9, SIGNAL(clicked()), this, SLOT(slotWritePrtButtonPushed()));
    //перейти по адресу
    connect (ui->pushButton_12, SIGNAL(clicked()), this, SLOT(slotJumpButtonPushed()));


    connect( &dbg, &Debug_Operations_Class::signalWritePort, this, &MainWindow::writeData);





    //lineEdit - path to ReportFiles, Stand: ui->comboBox_26, Module Numb: ui->comboBox_25, Module Name: ui->comboBox_26
    if (status_struct.isPSImode)
        report_file = new Report(ui->lineEdit->text(), ui->comboBox_24->currentText(),
                                 ui->comboBox_25->currentText(), ui->comboBox_26->currentText());

/*
    connect(ui->checkBox_10, &QCheckBox::clicked, this,  [this] {ui->checkBox_10->isChecked() ? ui->lineEdit_18->setEnabled(true) : ui->lineEdit_18->setEnabled(false); });


     connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::slotSetWrkFilesDir);
     connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::slotSetWrkFilesDir);*/
     connect(ui->action_5, &QAction::triggered, this, &MainWindow::openButtonClicked);





//     connect(ui->action_14, &QAction::triggered, this, )
     emit signalSendMessageToEdit(tr("Используется конфигурационный файл %1").arg(ini_file.fileName()));
     if (cmdCodes.isEmpty())
        emit signalSendMessageToEdit(tr("В конфигурационном файле не обнаружен список кодов модулей!"));

     //Библиотека USB
     int bLoad = LoadUSBLib( QDir::currentPath() + "/MP709.dll" );
     if (bLoad == -1) {
         emit signalSendMessageToEdit(QString (tr("Библиотека MP709.dll не обнаружена в каталоге %1")).arg( QDir::currentPath().toUtf8().data()));
     }
     else if (bLoad == -2)
         emit signalSendMessageToEdit(QString(tr("Ошибка при подгрузке функций из библиотеки MP709.dll")));
}

void MainWindow::writeOldCodeNumbersToIni() {
    QStringList codes;
    codes << "0F0E01560F0E0100" << "0F0E01560F0E0145" << "0F0E01560F0E0143" << "0F0E01560F0E0144" <<
             "0F0E01560F0E0141" << "0F0E01570F0E014C" << "0F0E01560F0E01D0" << "0F0E01560F0E01D1" <<
             "0F0E01560F0E0101" << "0F0E01560F0E0150" << "0F0E01560F0E0146";
    int i = 0;
    ini_file.beginGroup(MODULE_CODES);
    for ( auto code_str : codes   ) {
        setValueToIniFile( MODULE_CODES, QString::number(i, 10), code_str );
        i++;
    }
    ini_file.endGroup();
    emit signalSendMessageToEdit(tr("Коды записаны в конфигурационный файл, перезапустите приложение"));
}

void MainWindow::slotAddDataToQueue (const QByteArray &ba) {
    qqq.enqueue(ba);
}

void MainWindow::slotMemOpCheckBox(bool ch) {
    if (ch) {
        ui->pushButton_10->setText(tr("Считать в файл"));
        ui->pushButton_11->setText(tr("Отправить из файла"));
        ui->lineEdit_10->setEnabled(true);
        ui->lineEdit_10->setFocus();
        ui->comboBox_27->setEnabled(true);
    }
    else {
         ui->pushButton_10->setText(tr("Считать"));
         ui->pushButton_11->setText(tr("Отправить"));
         ui->lineEdit_10->setEnabled(false);
         ui->comboBox_27->setEnabled(false);
    }
}

void MainWindow::slotShowDataToConsole( QByteArray &ba ) {
    int pos=0;
    int sm=0;
    while((sm = ba.indexOf("\n\r", pos)) != -1 ) {
        ba = ba.remove(sm, 2);
        ba = ba.insert(sm, '\n');
        ++pos;
    }
    if (ui->radioButton_4->isChecked()) {
        m_console->putData( ba );

    } else if (ui->radioButton_5->isChecked()) {
         m_console->putDataRus(ba);

    } else if (ui->radioButton_6->isChecked()) {
        ba = ba.toHex();
        m_console->putData(ba);
    }
}

void MainWindow::repaintBorderLines(QLineEdit *lineEd, bool isError) {
    if (isError)
        lineEd->setStyleSheet("font-size: 10pt;  border-style: outset; border-width: 2px; border-color: #ff5500");
    else
        lineEd->setStyleSheet("font-size: 10pt; border-width: 1px; border-color: #e7e7e7");
//      lineEd->setStyleSheet("font-size: 12pt;  border-top-color: ##a2a2a2; border-width: 1px; border-color: #e7e7e7");
}

void MainWindow::paintStartInterface() {
    for (int i=0; i<lineEdVect.count(); i++)
        repaintBorderLines(lineEdVect.at(i), false);
}

quint32 MainWindow::getOperationSize() {
    quint32 size = 1;
    if (ui->comboBox_8->currentText().at(0) == '2')  {
        size = 2;
    }
    else  if (ui->comboBox_8->currentText().at(0) == '4')  {
        size = 4;
    }
    return size;
}

void MainWindow::slotReadButtonPushed() {
    paintStartInterface();
    if ( spinBox_1->text().isEmpty() ) {
        spinBox_1->setFocus();
        QMessageBox::warning(0, tr("MonQ"), tr("Введите адрес!"), QMessageBox::Ok);
        return;
    }
    bool ok;
    quint32 addrH = spinBox_1->text().toUInt(&ok, 16);
    if (ui->checkBox_9->isChecked())  {
        //читаем из памяти в файл
        if (ui->lineEdit_10->text().isEmpty()) {
            repaintBorderLines(ui->lineEdit_10, true);
            ui->lineEdit_10->setFocus();
            QMessageBox::critical(this, tr("MonQ"), tr("Введите количество считываемых байт."),
                                  QMessageBox::Ok);
        }
        else {
            repaintBorderLines(ui->lineEdit_10, false);
            WriteToLOG("Чтение из памяти 0x"+spinBox_1->text()+" в файл");
            WriteToStatus(tr("Чтение из памяти в файл..."));
            int Sz = ui->lineEdit_10->text().toInt(&ok, 10);
            QString path;
            getValueFromIni(WORK_DIRS, GET_FROM_MEM_ADDR, path );
            if (path.isEmpty()) path = QDir::currentPath();
            QString filename = QFileDialog::getSaveFileName(0, "SaveDialog", path, "*.bin *.BIN;; All Files(*);; *.com *.COM");
            if (!filename.isEmpty()) {
                setValueToIniFile(WORK_DIRS, GET_FROM_MEM_ADDR, QDir(filename).absolutePath() );
                emit signalSendMessageToEdit(tr("Производится запись %1 байтов в файл %2").arg(Sz).arg(filename));
                dbg.MemReadToFile(addrH, filename, Sz );
            }
            else {
                emit signalSendMessageToEdit(tr("Файл для записи не выбран!"));
                WriteToStatus(tr(" "));
            }
        }
    }
    else {
        //одиночная операция
        quint32 cmdType = READ_MEM_BYTE;
        quint32 size = getOperationSize();
        ( size == 1 ) ? cmdType = READ_MEM_BYTE : ( size == 2 ) ? cmdType = READ_MEM_WORD : cmdType = READ_MEM_DWORD;
        WriteToLOG("Чтение из памяти 0x"+ spinBox_1->text() );
        WriteToStatus(tr("Чтение из памяти.."));
        dbg.MemRead(addrH, cmdType);
    }
}



void MainWindow::slotChoosePathRprtCapture() {
    QString dir = nullptr;
    QString fieldName;
    QLineEdit *outLine = ui->lineEdit;
    if (QObject::sender() == ui->toolButton_2) {
        fieldName = RPRT_PATH;
        outLine = ui->lineEdit;
    }
    else if (QObject::sender() == ui->toolButton_3) {
        fieldName = CAPTURE_PATH;
        outLine = ui->lineEdit_2;
    }
    getValueFromIni( WORK_DIRS, fieldName, dir );
    if (dir.isEmpty()) dir = QDir::currentPath();
    QString filename = QFileDialog::getExistingDirectory(this, "Select Directory", dir,  QFileDialog::ShowDirsOnly
                                                         | QFileDialog::DontResolveSymlinks);
    if ( filename.isEmpty()) {
        filename = QDir::currentPath();
    }
    setValueToIniFile(WORK_DIRS, fieldName, filename);
    outLine->setText(filename);
}

void MainWindow::init_statusVariables() {
    status_struct.isPSImode = false;
    getValueFromIni(WORK_MSG, PSI_MODE_BOOl, status_struct.isPSImode);
    status_struct.isPSImode ? ui->action_25->setChecked(true) : ui->action_26->setChecked(true);

    status_struct.isNewBios = false;
    getValueFromIni(MODULE_INFO, NEW_BIOS_CHECK, status_struct.isNewBios);
    ui->checkBox_2->setChecked(status_struct.isNewBios);
}

void MainWindow::slotSwitchMode(bool checked) {
    if ( QObject::sender() == ui->action_25 ) {
        status_struct.isPSImode = checked;
        ui->action_26->setChecked(!checked);
        emit signalSendMessageToEdit("PSI");
    }
    else {
        status_struct.isPSImode = !checked;
        ui->action_25->setChecked(!checked);
        emit signalSendMessageToEdit("Dbg");
    }
    setValueToIniFile(WORK_MSG, PSI_MODE_BOOl, status_struct.isPSImode);
}


//-----------------------------------------------------------------------
void MainWindow::slotShowMessageInfo( const QString &msg ) {
    ui->textEdit_4->append(msg);
}
//-----------------------------------------------------------------------
void MainWindow::print_message( const unsigned int &type, char *fmt, ...)
{
//    if (type == MSG_TYPE_LOG_WR &&  !Form1->Status.UseLog)
//        return;
//    if (type == MSG_TYPE_RPRT_WR &&  !Form1->Status.Report)
//        return;
//    if (type == MSG_TYPE_RPRT_WR_TIME &&  !Form1->Status.Report)
//        return;
//    if (type == MSG_TYPE_RPRT_WR_DT_TIME &&  !Form1->Status.Report)
//        return;
//    if (type == MSG_TYPE_PSI_STAT &&  !Form1->PSI_mode)
//        return;

//    std::string wrStr;
//    wrStr.clear();
//    AnsiString ss;
//    AnsiString tm = "hh:nn:ss";
//    bool addBraket = true;
//    if (fmt) {
//        va_list obj;
//        int d = 0;
//        char *str;
//        char val_out[9];
//        va_start( obj, fmt );
//        int type = 0;
//        for (char *ch = fmt; *ch; ++ch ) {
//            if (*ch != '%') {
//                wrStr.push_back(*ch);
//                continue;
//            }
//            switch( *++ch ) {
//                case 'x':
//                    d = va_arg(obj, DWORD);
//                    sprintf(val_out, "%x", d );
//                    wrStr = wrStr.append(val_out);
//                    break;
//                case 'd':
//                    d = va_arg(obj, int);
//                    wrStr = wrStr.append(IntToStr(d).c_str());
//                    break;
//                case 's':
//                    str = va_arg(obj, char *);
//                    if (str != NULL ) {
//                        wrStr = wrStr.append(str);
//                    }
//                    break;
//                default:
//                    wrStr.push_back(*ch);
//            }
//        }
//        va_end(obj);
//    }

//    switch (type) {
//        case MSG_TYPE_ERR_BOX:
//            MessageBox( NULL, wrStr.c_str(), Form1->getMsgFromVector( ERROR_TITLE ).c_str(), MB_OK|MB_ICONERROR|MB_TASKMODAL );
//            break;
//        case MSG_TYPE_WRN_BOX:
//            MessageBox( NULL, wrStr.c_str(), Form1->getMsgFromVector( WARNING_TITLE ).c_str(), MB_OK|MB_ICONWARNING );
//            break;
//        case MSG_TYPE_LOG_WR:
//            Form1->LogFileWrite(AnsiString(wrStr.c_str()));
//            break;
//        case MSG_TYPE_RPRT_WR:
//        case MSG_TYPE_RPRT_WR_TIME:
//        case MSG_TYPE_RPRT_WR_DT_TIME:
//            if (type == MSG_TYPE_RPRT_WR_TIME) {
//                wrStr.append( (" " + Now().CurrentTime().FormatString(tm)).c_str());
//            }
//            else if ( type == MSG_TYPE_RPRT_WR_DT_TIME ) {
//                wrStr.append( (" " + Now().CurrentDateTime().DateTimeString() ).c_str());
//            }
//            else {
//                if (wrStr == RPRT_EMPTY_STR ) {
//                    wrStr.append("\n");
//                    addBraket=false;
//                }
//            }
//            Form1->WriteToReportFile( wrStr.c_str(), addBraket  );
//            break;
//        case MSG_TYPE_STAT_WR:
//            Form1->sendMsgToStatus(wrStr.c_str(), true );
//            break;
//        case MSG_TYPE_PSI_STAT:
//       /*		if (Form1->PSI_mode)
//                Form1->StatusBar2->Panels->Items[0]->Text = AnsiString(wrStr.c_str());
// */			break;
//        case MSG_TYPE_PSI_STATBAR:
//            if (Form1->PSI_mode)
//                Form1->sendMsgToStatus(wrStr.c_str(), true );
//            break;

 //   }
}

std::string MainWindow::GetReportName(){


}
void MainWindow::portOpReadData() {
 /*   bool opRes;
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
//    op->begin_operation();*/


}


void MainWindow::memOpReadData() {
   /* bool opRes;
    quint32 addr = ui_mem->lineEdit_5->text().toUInt(&opRes, 16);
    int size = 1;
    monOperations *op;
    if (ui_mem->checkBox_3->isChecked()) {
        opInfo.opState = State::ReadFile;
        opInfo.opFile = ui_mem->lineEdit_13->text();
        opInfo.fileChSm = 0;
        opInfo.wrkSz = 0;
        //open file and clean it, then close again
        QFile fl(opInfo.opFile);
        fl.open(QIODevice::WriteOnly | QIODevice::Truncate);
        fl.close();
        size = lineEdit_8->removeSpaces().toInt();
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
    op->begin_operation();*/
}

void MainWindow::memOpWriteData() {
  /*  if (ui_mem->lineEdit_10->text().isEmpty()) {
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
        repTimes = lineEdit_7->text().toInt();
        needInfo = true;
    }

    while( repTimes ) {
        if (needInfo) {
            printRdData("info", QString::number(repTimes));
        }
        ui->textEdit->insertPlainText(QString::number(repTimes));
        operation_size = size;
        main_state = State::WriteMem;
  /*    monOperations *op = new monOperations(this, main_state, addr, size, data);
        connect(op, &monOperations::signalWriteArrayToPort, this, &MainWindow::writeData );
        op->begin_operation();*/
  //      repTimes--;*/
   // }



//    if (needInfo) {
//        printRdData("info", tr("Операция завершена"));
//    }

}




void MainWindow::selectFileMemOp() {
//    QString dir = "", pref = "";
//    getValueFromIni( WorkingDirectories, LoadFileToMemory_path, dir );
//    getValueFromIni("WorkingDirectories", "Prefix", pref );
//    QString filename = QFileDialog::getOpenFileName(0, "OpenDialog", dir.isEmpty() ? QDir::currentPath() : dir,
//                           pref.isEmpty() ? "Data files(*.bin);;COM files(*.com);;All files(*.*)" : pref  );
//    if (!filename.isEmpty()) {
//        setValueToIniFile(WorkingDirectories, LoadFileToMemory_path, QFileInfo(filename).path());
//        ui_mem->lineEdit_13->setText(filename);
//        lineEdit_8->setText( QString::number(QFileInfo(filename).size()));
//   //     memLoadFile flMem(filename);
//   //     connect(&flMem, &memLoadFile::showMemFileSize, this, []() { qDebug() << "val"/*ui_mem->lineEdit_8->setText(QString::number(val))*/;} );
//    }
}



void MainWindow::createToolBars() {
//  ui->toolBar->addAction(new QAction(tr("Очистить экран"), this));
//  QLabel *lbl = new QLabel("aaaaaaaa");
//  ui->toolBar->addWidget(lbl);

}

void MainWindow::addLineToTable(const QVector<QVector<QString>> &lines) {
//    ui->tableWidget_2->setRowCount(lines.size());
//    for (int i=0; i<lines.size(); ++i) {
//        for (int j=0; j<4; ++j) {
//            QTableWidgetItem *item = new QTableWidgetItem(lines.at(i).at(j));
//            ui->tableWidget_2->setItem(i, j, item);
//       }
//    }
//    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode( 2, QHeaderView::Stretch);
}

void MainWindow::showScript(const QString &filename) {
//    QList<QString>names;
//    for (int i = 0; i < ui->comboBox_8->count(); ++i) {
//         names.push_back(ui->comboBox_8->itemText(i));
//    }
//    int ind = names.indexOf(filename);
//    qDebug() << ind;
//    if ((ind != -1) && (ind)) {
//        names.swap(0, ind);
//    //    ui->comboBox_8->clear();
//     //   ui->comboBox_8->addItems(names);
//    }
//    else {
// //       ui->comboBox_8->insertItem(0, filename);
//    }
//  //  ui->comboBox_8->setCurrentIndex(0);
//    qDebug() << "\n Here!\n";

//    DbgClass openS(filename, mCmd);
//    tableLines = openS.showTable();
//    addLineToTable(tableLines);
}

void MainWindow::openButtonClicked() {
   // ScptFl.ItemChanged = false; //Tamara
    QString dir;
    getValueFromIni(WORK_DIRS, OPEN_SCRIPTS, dir);
    QString filename = QFileDialog::getOpenFileName(0, "OpenDialog", dir.isEmpty() ? QDir::currentPath() : dir, "*.dbg");
    if (!filename.isEmpty()) {
        setValueToIniFile(WORK_DIRS, OPEN_SCRIPTS, QDir(filename).absolutePath() );

    }

    int a = 0;


//	OpenDlg->Filter = "Debug files (*.dbg)|*DBG";
//	OpenDlg->Options << ofNoChangeDir;
//	OpenDlg->InitialDir = Form1->Ini->ReadString(WORK_DIRS, OPEN_SCRIPTS, Form1->path);
//	if ( OpenDlg->InitialDir.IsEmpty() )
//		OpenDlg->InitialDir = Form1->path;

//	OpenDlg->Execute();
//	AnsiString OpenScrptName = OpenDlg->FileName;
//	if ( !OpenScrptName.IsEmpty() ) {
//		Form1->Ini->WriteString(WORK_DIRS, OPEN_SCRIPTS, ExtractFilePath( OpenScrptName ));
//		FILE *OpenScrptPtr = fopen( OpenScrptName.c_str(), "r+b");
//		if ( OpenScrptPtr ) {
//			if ( Form1->PageControl3->ActivePageIndex == ACTIVE_INDX_GRID || Form1->PSI_mode) {
//				Form1->addFilenameToCombo(Form1->WrkComboBox, OpenScrptName );
//				Form1->saveComboFilesToIni(Form1->WrkComboBox, SCRIPT_LIST );
//			}
//			Form1->print_message( MSG_TYPE_STAT_WR, FILE_OPEND, OpenScrptName );
//			Form1->Status.TextView ? script->loadDataFromFile(OpenScrptName, Form1->ListBox1) : script->loadDataFromFile(OpenScrptName, Form1->ListView1 ) ;
//			fclose( OpenScrptPtr );
//			CheckScriptErrors();
//		}
//	}
//	delete OpenDlg;




//    if (!filename.isEmpty()){
//        showScript(filename);
//    }
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
        emit signalSendMessageToEdit(m_serial->errorString());
        QMessageBox::critical(this, tr("Critical Error"), m_serial->errorString());
        closeSerialPort();
    }
}


void MainWindow::printRdData(const QString &marker, const QString &data) {
//    ui_mem->label_4->clear();
//    if (marker == "mr") {
//        ui_mem->lineEdit_12->clear();
//        ui_mem->lineEdit_12->setText(data);
//    }
//    else if (marker == "err"  || marker == "info") {
//        ui_mem->label_4->setStyleSheet(QString("font-size: %1px").arg(12));
//        ui_mem->label_4->setText(data);
//    }
//    else if (marker == "pr") {
//        ui_mem->lineEdit_4->setText(data);
//    }
}


void MainWindow::readData() {
    QMutexLocker locker(&mutex);
    const QByteArray data = m_serial->readAll();
    slotAddDataToQueue(data);
//    emit signalSendDataArray(data);
  /*  parseData p(this, data, &opInfo, operation_size );
    connect(&p, &parseData::showData, this, &MainWindow::showString);
    connect(&p, &parseData::printDataInField, this, &MainWindow::printRdData);
    p.parser();*/
}

void MainWindow::writeData( const QByteArray &data ) {
    m_serial->write(data);
}


void MainWindow::showString( const QString &str ) {
    ui->textEdit->insertPlainText(str);
}

void MainWindow::manageSerialPort() {
    bool bSetTrue = false;
    if ( !ui->actionConnection->isChecked()) {
        closeSerialPort();
    }
    else {
        if ( openSerialPort() != -1) {
            bSetTrue = true;
        }
    }
    //changeEnableMode(bSetTrue);
}

void MainWindow::closeEvent(QCloseEvent *event) {
//    if (memForm) delete memForm;
//    if (portForm) delete portForm;

    setValueToIniFile(APP_INFO, ACTIVE_PAGE, ui->tabWidget->currentIndex() );
}



MainWindow::~MainWindow() {
//    closeSerialPort();
    saveSettings();
//    delete ui;
}

qint8 MainWindow::openSerialPort() {
   if (!ui->comboBox_3->currentText().isEmpty()) {
       m_serial->setPortName( ui->comboBox_3->currentText() );
   }
   else {
       QMessageBox::critical(this, tr("Ошибка подключения"),
            tr("Не указан номер COM-порта"));
       emit signalSendMessageToEdit( tr("Ошибка - не указан номер COM-порта!"));
       return -1;
   }

   if (!ui->comboBox_4->currentText().isEmpty())
       m_serial->setBaudRate( ui->comboBox_4->currentText().toInt());
   else {
       QMessageBox::critical(this, tr("Ошибка подключения"),
            tr("Не указана скорость работы COM-порта"));
       emit signalSendMessageToEdit( tr("Ошибка - не указана скорость работы COM-порта!"));
       return -1;
   }

   if ( ui->comboBox_7->currentText().isEmpty() ) {
       QMessageBox::critical(this, tr("Ошибка подключения"),
            tr("Не указано количество стоповых бит COM-порта"));
       emit signalSendMessageToEdit( tr("Ошибка - не указано количество стоповых бит COM-порта!"));
       return -1;
   }
   float stop_v = ui->comboBox_7->currentText().toFloat();
   if  (stop_v == 1)
        m_serial->setStopBits(QSerialPort::OneStop);
   else if (stop_v == 1.5)
       m_serial->setStopBits(QSerialPort::OneAndHalfStop);
   else if (stop_v == 2)
       m_serial->setStopBits(QSerialPort::TwoStop);
   else
       m_serial->setStopBits(QSerialPort::OneStop);

   if ( ui->comboBox_6->currentText().isEmpty() ) {
       QMessageBox::critical(this, tr("Ошибка подключения"),
            tr("Не указана четность COM-порта"));
       emit signalSendMessageToEdit( tr("Ошибка - не указана четность COM-порта!"));
       return -1;
   }
   QString par_str = ui->comboBox_6->currentText();
   if (par_str == "No")
        m_serial->setParity( QSerialPort::NoParity);
   else if (par_str == "Even")
       m_serial->setParity (QSerialPort::EvenParity);
   else if (par_str == "Odd")
       m_serial->setParity ( QSerialPort::OddParity);
   else m_serial->setParity( QSerialPort::NoParity);

   if ( ui->comboBox_5->currentText().isEmpty() ) {
       QMessageBox::critical(this, tr("Ошибка подключения"),
            tr("Не указано число битов данных COM-порта"));
       emit signalSendMessageToEdit( tr("Ошибка - не указано число битов данных COM-порта!"));

       return -1;
   }

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
       return -1;
   }
   return 0;
}

void MainWindow::changeEnableMode( bool setTrue ) {
  //  ui->menu_11->setEnabled(setTrue);

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
//    lst=lst.toSet().toList();
//    int  i = 0;
//    for (const auto  &str : lst ) {
//        ini_file.setArrayIndex(i);
//        ini_file.setValue("name", lst.at(i));
//        i++;
//    }
//    ini_file.endArray();
//    ini_file.sync();
}

void MainWindow::slotReadFromIniToCombo(QComboBox *cmb) {
    QString keyNm;
    if (cmb == ui->comboBox_26) keyNm = MODUL_NAMES_LIST;
    else if (cmb == ui->comboBox_25) keyNm = MODUL_NUMBERS_LIST;
    else if (cmb == ui->comboBox_24) keyNm = STEND_NAMES_LIST;
    else if (cmb == ui->comboBox) keyNm = SCRIPT_LIST;
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
    setValueToIniFile(APP_INFO, FORM_LEFT, MainWindow::geometry().x());
    setValueToIniFile(APP_INFO, FORM_TOP, MainWindow::geometry().y());
    setValueToIniFile(APP_INFO, FORM_HEIGHT, MainWindow::height());
    setValueToIniFile(APP_INFO, FORM_WIDTH, MainWindow::width());
    setValueToIniFile(WORK_DIRS, RPRT_PATH, ui->lineEdit->text());
    setValueToIniFile(WORK_DIRS, CAPTURE_PATH, ui->lineEdit_2->text());
    slotWriteComboToIni(SKRPTNAME_KEY, ui->comboBox);
    ini_file.sync();
}


void MainWindow::restoreSettings() {
    //Восстанавливаем положение на экране + размеры
    QVector<int>params;
    int val;
    getValueFromIni( APP_INFO, FORM_LEFT, val);
    params.push_back(val);
    getValueFromIni(APP_INFO, FORM_TOP, val),
    params.push_back(val);
    getValueFromIni(APP_INFO, FORM_HEIGHT, val);
    params.push_back(val);
    getValueFromIni(APP_INFO, FORM_WIDTH, val);
    params.push_back(val);
    MainWindow::setGeometry( params.at(0), params.at(1), params.at(3), params.at(2));

    //В Windows 10 не прорисовываются кое-где границы
/*     if(QSysInfo::windowsVersion()==QSysInfo::WV_WINDOWS10){
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
     }*/
    int indx = 0;
    getValueFromIni(APP_INFO, ACTIVE_PAGE, indx);
    if ( status_struct.isPSImode ) {
        if (indx != 3) indx = 0;
    }
    else
        if (indx == 3) indx = 0;
    ui->tabWidget->setCurrentIndex( indx );
    QString str = nullptr;
    getValueFromIni(WORK_DIRS, RPRT_PATH, str);
    ui->lineEdit->setText(str);
    getValueFromIni(WORK_DIRS, CAPTURE_PATH, str);
    ui->lineEdit_2->setText(str);
    //Memory operations TAB
    //I/O
    getValueFromIni(WORK_PARAMS, PORT_READ_ED, str);
    ui->lineEdit_8->setText(str);
    getValueFromIni(WORK_PARAMS, PORT_WRITE_ED, str);
    ui->lineEdit_9->setText(str);
    //Memory
    ui->spinBox->setVisible(false);
    ui->spinBox_2->setVisible(false);
    //Jump
    ui->spinBox_3->setVisible(false);

    cmdCodes.clear();
    //Сохраняем коды модулей в память
    indx=0;
    str = "";
    ini_file. beginGroup(MODULE_CODES);
    QStringList keys = ini_file.allKeys();
    if ( keys.count() != -1) {
        for(indx = 0; indx < keys.count(); ++indx ) {
            getValueFromIni(MODULE_CODES, QString::number(indx, 10), str );
            cmdCodes.push_back(str);
        }
    }
    ini_file.endGroup();
     //список сценариев
     slotReadFromIniToCombo(ui->comboBox);
}

void MainWindow::connectInterface( bool setConnected ) {
    if ( setConnected ) {
        connectMsg = tr("Подключено к ")+ui->comboBox_3->currentText();
    }
    else {
        connectMsg = tr("Отключено");
    }
    emit signalSendMessageToStatusBar(connectMsg);

    ui->comboBox_3->setEnabled(!setConnected);
    ui->comboBox_4->setEnabled(!setConnected);
    ui->comboBox_5->setEnabled(!setConnected);
    ui->comboBox_6->setEnabled(!setConnected);
    ui->comboBox_7->setEnabled(!setConnected);
    ui->comboBox_9->setEnabled(!setConnected);
    ui->comboBox_10->setEnabled(!setConnected);
    ui->action_6->setEnabled(setConnected);
    ui->action_7->setEnabled(setConnected);
    ui->action_8->setEnabled(setConnected);

//    ui->pushButton_2->setEnabled(setConnected);
}

void MainWindow::init_statusBar() {

    ui->statusBar->setVisible(true);
    ui->statusBar->showMessage(QString(DISCONNECT_MSG_STATUS_BAR));
    //emit signalSendMessageToStatusBar(static_cast<const QString &>(DISCONNECT_MSG_STATUS_BAR));
 /*   ui->statusBar->insertWidget(STATUS_BAR_CONNECTION_INFO, new QLabel(tr("Отключено")));
    ui->statusBar->insertWidget( STATUS_BAR_CONNECT_TIMER, new QLabel("00:00:00"));*/

 /*   timer_connection = new ConTimer();
    timer_connection->setInterval(1000);*/

   // connect(timer_connection, &ConTimer::timeout, timer_connection, &ConTimer::slotCountConnectionTime);
   // connect(timer_connection, &ConTimer::signalOutTimer, this, &MainWindow::slotShowStatusBarInfo);
}

void MainWindow::slotShowStatusBarInfo(const QString &msg ) {
    // ui->statusBar->showMessage("AAAAAAAAAA");
  /*  if (msg == DISCONNECT_MSG_STATUS_BAR)
        ui->statusBar->showMessage(QString(DISCONNECT_MSG_STATUS_BAR) + " " + "00:00:00");
    else*/
        ui->statusBar->showMessage( msg );
}


void MainWindow::init_comboBoxes() {
    QString str;
    getValueFromIni(CON_INFO, COM_NUMB_CMB, str);
    updateComInfo( ui->comboBox_3 );
    if (!str.isEmpty()) ui->comboBox_3->setCurrentText(str);

    QStringList lst;
    lst << "921600" << "460800" << "230400"  << "115200" <<  "57600" <<"38400" <<"19200" <<"9600" << "4800";
    ui->comboBox_4->addItems(lst);
    ui->comboBox_4->setMaxVisibleItems(4);
    getValueFromIni(CON_INFO, COM_SPEED_CMB, str);
    if (!str.isEmpty()) ui->comboBox_4->setCurrentText(str);
    lst.clear();

    lst << "5" << "6" << "7" << "8";
    ui->comboBox_5->addItems(lst);
    getValueFromIni(CON_INFO, COM_DATA_BITS_CMB, str);
    if (!str.isEmpty()) ui->comboBox_5->setCurrentText(str);
    lst.clear();

    lst << "No" << "Even" << "Odd";
    ui->comboBox_6->addItems(lst);
    getValueFromIni(CON_INFO, COM_PARITY_CMB, str);
    if (!str.isEmpty()) ui->comboBox_6->setCurrentText(str);
    lst.clear();

    lst<< "1" << "1,5" << "2";
    ui->comboBox_7->addItems(lst);
    getValueFromIni(CON_INFO, COM_STOP_CMB, str);
    if (!str.isEmpty()) ui->comboBox_7->setCurrentText(str);
    lst.clear();

    lst << "x86" << "Power PC" << "MIPS" <<"ARM" << "DSP" << "NIOS";
    ui->comboBox_9->addItems(lst);
    getValueFromIni(MODULE_INFO, ARCH_CMB, str);
    sortAlphabetically(ui->comboBox_9);
    if (!str.isEmpty()) ui->comboBox_9->setCurrentText(str);
    lst.clear();

    lst << "32 bits"  << "64 bits";
    ui->comboBox_10->addItems(lst);
    getValueFromIni(MODULE_INFO, BUS_CMB, str);
    if (!str.isEmpty()) ui->comboBox_10->setCurrentText(str);
    lst.clear();

    lst<<tr("1 байт") << tr("2 байта") << tr("4 байта");
    ui->comboBox_8->addItems(lst);
    getValueFromIni(WORK_PARAMS, READ_WRITE_SIZE, str);
    if (!str.isEmpty()) {
        ui->comboBox_8->setCurrentText(str);
        int step_val = getOperationSize();
        spinBox_1->setSingleStep( step_val );
        spinBox_2->setSingleStep( step_val );
        spinBox_3->setSingleStep( step_val );
    }
    lst.clear();
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
         setValueToIniFile(CON_INFO, COM_PARITY_CMB, str);
    }
    else if (QObject::sender() == ui->comboBox_3) {
        setValueToIniFile(CON_INFO, COM_NUMB_CMB, str);
    }
    else if (QObject::sender() == ui->comboBox_7) {
         setValueToIniFile(CON_INFO, COM_STOP_CMB, str);
    }
    else if (QObject::sender() == ui->comboBox_5) {
        setValueToIniFile(CON_INFO, COM_DATA_BITS_CMB, str);
    }
    else if (QObject::sender() == ui->comboBox_4) {
         setValueToIniFile(CON_INFO, COM_SPEED_CMB, str);
     }
     else if (QObject::sender() == ui->comboBox_10) {
        setValueToIniFile(MODULE_INFO, BUS_CMB, str);
        setValidatorsFunc(ui->comboBox_10);
    }
    else if (QObject::sender() == ui->comboBox_9) {
        setValueToIniFile(MODULE_INFO, ARCH_CMB, str);
    }
    else if (QObject::sender() == ui->comboBox_8 ) {
        setValueToIniFile(WORK_PARAMS, READ_WRITE_SIZE, str);
        int step_val = getOperationSize();
        spinBox_1->setSingleStep( step_val );
        spinBox_2->setSingleStep( step_val );
        spinBox_3->setSingleStep( step_val );
    }
/*
    else if (QObject::sender() == ui_mem->comboBox_12) {
        setValueToIniFile(PANEL_MEM_OP, READ_SIZE, str);
    }
    else if (QObject::sender() == ui_mem->comboBox_15) {
        setValueToIniFile(PANEL_MEM_OP, WRITE_SIZE, str);
    }*/
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
    for (const QSerialPortInfo &serialPortInfoList : QSerialPortInfo::availablePorts())
        cb->addItem(serialPortInfoList.portName());
    sortAlphabetically(cb);
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
 //   qDebug() << group << " " << section << " " << value << endl;
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


void MainWindow::slotChangeOutputCodec() {

    if ( QObject::sender() == ui->radioButton_4 ) {
        //ANSI
       setValueToIniFile(APP_INFO, ANSI_OUT, true);
       setValueToIniFile(APP_INFO, OEM_OUT, false);
       setValueToIniFile(APP_INFO, HEX_OUT, false);

    }
    else if ( QObject::sender() == ui->radioButton_5 ) {
        //OEM
        setValueToIniFile(APP_INFO, ANSI_OUT, false);
        setValueToIniFile(APP_INFO, OEM_OUT, true);
        setValueToIniFile(APP_INFO, HEX_OUT, false);
    }
    else if ( QObject::sender() == ui->radioButton_6 ) {
        //HEX
        setValueToIniFile(APP_INFO, ANSI_OUT, false);
        setValueToIniFile(APP_INFO, OEM_OUT, false);
        setValueToIniFile(APP_INFO, HEX_OUT, true);
    }

}
void MainWindow::setCodecs() {
    //Кодеки
//     QMenu *menu_codec = new QMenu;
//     menu_codec->setTitle(tr("Кодировка текста сценария"));
//     ui->menu_2->addMenu(menu_codec);
//     actUtf8CodecSet = new QAction(tr("UTF-8"), this);
//     actWinCodecSet = new QAction( tr("Windows-1251"), this);
//     menu_codec->addAction(actUtf8CodecSet);
//     menu_codec->addAction(actWinCodecSet );
//     actUtf8CodecSet->setCheckable(true);
//     actWinCodecSet->setCheckable(true);
//     //если обе кодировки не установлены, по умолчанию виндовая
//     bool isUtf8 = false;
//     getValueFromIni(APP_INFO, CODEC_UTF8, isUtf8) ;
//     actUtf8CodecSet->setChecked(isUtf8);
//     getValueFromIni(APP_INFO, CODEC_WIN, isUtf8) ;
//     actWinCodecSet->setChecked(isUtf8);
//     connect(actUtf8CodecSet, &QAction::toggled, this, SLOT(slotChangeCodecUtf8(bool)));
//     connect(actWinCodecSet, SIGNAL(toggled(bool)), SLOT(slotChangeCodecWin(bool)));
//     if (( actUtf8CodecSet->isChecked() && actWinCodecSet->isChecked()) || ( !actUtf8CodecSet->isChecked() && !actWinCodecSet->isChecked())) {
//         actWinCodecSet->setChecked(true);
//     }
}
