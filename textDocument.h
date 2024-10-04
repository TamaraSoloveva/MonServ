#ifndef TEXTDOCUMENT_H
#define TEXTDOCUMENT_H

#include "MAIN_INCLUDES.h"

#include "mainwindow.h"

#include  <fstream>
#include <QObject>


class TextDocument : public QObject
{
    Q_OBJECT

    std::string filename;
    std::ofstream *wr_file;
    TextFileTypes T;

//    template <TextFileTypes T>
//    QString getHomeDirectory();

public:
    TextDocument( const std::string & f_n );
    TextDocument() {}
    virtual ~TextDocument();
    void WriteData( const std::string & txt );
signals:
    void signalNotOpened( const std::string &filename );
};

//template<>
//QString TextDocument::getHomeDirectory<Report_type>() { QString aaa = "aaa"; return aaa;}

class Report : public TextDocument {
    QString report_path;
    QString stand_name, module_number, module_name;
public:
   // Report( const QString & f_n );
    Report( const QString & f_n, const QString & stnd, const QString & nmb, const QString & mdl);
    virtual ~Report(){};
};

#endif // TEXTDOCUMENT_H
