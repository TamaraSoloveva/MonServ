#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QVector>
#include <QShortcut>

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

    void init_comboBoxes();
    void updateComInfo( QComboBox *cb);
    void sortAlphabetically(QComboBox *cB);

    void getValueFromIni(const QString &group, const QString &section, int &value);
    void getValueFromIni(const QString &group, const QString &section, bool &value);
    void getValueFromIni(const QString &group, const QString &section, QString &value);

    void setValueToIniFile( const QString &group, const QString &section, const QString &val );
    void setValueToIniFile( const QString &group, const QString &section, const bool &val );
    void setValueToIniFile( const QString &group, const QString &section, const int &val );



};
#endif // MAINWINDOW_H
