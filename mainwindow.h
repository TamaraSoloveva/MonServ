#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QVector>
#include <QShortcut>
#include <QMessageBox>
#include <QTimer>

#include <QComboBox>

#include <QDebug>
#include "ui_MonServ.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Ui_MainWindow;

class MainWindow : public QMainWindow, public Ui_MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSettings ini_file;
    QSerialPort *m_serial = nullptr;


    void openSerialPort();
    void closeSerialPort();
    void writeData(const QByteArray &data);
    void readData();
    void connectInterface( bool setConnected );


    QVector<QLineEdit *>lineEdVect;

    void init_comboBoxes();
    void init_statusBar();
    void updateComInfo( QComboBox *cb);
    void sortAlphabetically(QComboBox *cB);
    void setValidatorsFunc(const QObject *var);

    void getValueFromIni(const QString &group, const QString &section, int &value);
    void getValueFromIni(const QString &group, const QString &section, bool &value);
    void getValueFromIni(const QString &group, const QString &section, QString &value);

    void setValueToIniFile( const QString &group, const QString &section, const QString &val );
    void setValueToIniFile( const QString &group, const QString &section, const bool &val );
    void setValueToIniFile( const QString &group, const QString &section, const int &val );

private slots:
    void slotReWrSettingsInIni( const QString & str );
    void manageSerialPort();
    void handleErrorFromPort(QSerialPort::SerialPortError error);



signals:




};
#endif // MAINWINDOW_H
