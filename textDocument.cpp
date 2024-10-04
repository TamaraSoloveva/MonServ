#include "textDocument.h"

#include "mainwindow.h"


TextDocument::TextDocument( const std::string & f_n ) : filename(f_n) {
    try {
        wr_file = new std::ofstream(filename);
    }
    catch (std::bad_alloc &exp) {
        emit signalNotOpened(filename);
    }
}

void TextDocument::WriteData( const std::string & txt ) {
    wr_file->write(txt.c_str(), txt.length());
}

TextDocument::~TextDocument() {
    delete wr_file;
}
//=============================================================================

Report::Report(const QString & f_n, const QString & stnd, const QString & nmb, const QString & mdl): report_path(f_n),
    stand_name(stnd), module_number(nmb), module_name(mdl) {
    std::string NewDir, ReportsDirIni;
    std::string ReportFileName;;
    std::string DateFrmt = "yyyy.mm.dd";
    std::string TimeFrmt = "hh.nn.ss";
    QString DtStr = QDateTime::currentDateTime().toString();
    QString slash;
#ifdef Q_OS_WIN
    slash = "\\";
#else
    slash = "/";
#endif
    QString dir = report_path + slash + DtStr + slash;





                    /*ReportsDirIni = dir + "\\" + DtStr + "\\";
                else {
                    ReportsDirIni = dir + "\\"+ ComboBox1->Text + "\\";
                    ReportsDirIni = ReportsDirIni + DtStr + "\\";
                }
                if ( !DirectoryExists( ReportsDirIni )) {
                    tmp = strtok(ReportsDirIni.c_str(), "\\");
                    while ( tmp ) {
                        NewDir += AnsiString(tmp);
                        NewDir += "\\";
                        if ( !DirectoryExists( NewDir ))
                            CreateDir( NewDir );
                        tmp = strtok( NULL, "\\");
                    }
                }
                else
                    NewDir =  ReportsDirIni;
    /*            AnsiString TimeStr = Now().CurrentTime().FormatString(TimeFrmt);
                TimeStr = StringReplace( TimeStr, ".", "", TReplaceFlags() << rfReplaceAll );
                if ( ComboBox3->Text.IsEmpty() ) {
                    if ( ComboBox2->Text.IsEmpty() )
                        ReportFileName = NewDir + " " + DtStr+"_" + TimeStr+".txt";
                    else
                        ReportFileName = NewDir + " " + ComboBox2->Text + " " + DtStr+"_" + TimeStr+".txt";
                }
                else {
                    if ( ComboBox2->Text.IsEmpty() )
                        ReportFileName = NewDir + " " + ComboBox3->Text + " " + DtStr+"_" + TimeStr+".txt";
                    else
                        ReportFileName = NewDir + ComboBox3->Text + " " + ComboBox2->Text + " " + DtStr+"_" + TimeStr+".txt";
                }
            }
            rpt = fopen( ReportFileName.c_str(), "a+t");
            if ( !rpt ) {
                print_message( MSG_TYPE_ERR_BOX, Form1->getMsgFromVector2(REPORT_OPEN_ERROR ));
                Form1->CheckBox1->Checked = false;
                return;
            }

            Form1->Ini->WriteString( WORK_DIRS, RPRT_PATH, ReportFileName );

            Status.Report = true;
            ControlReportMode( Status.Report );
            Form1->ComboBox7->Text = ReportFileName;
            Form1->ComboBox7->SelStart = Form1->ComboBox7->Text.Length();

            print_message( MSG_TYPE_STAT_WR, REPORT_OPEN, ReportFileName );
            print_message( MSG_TYPE_LOG_WR,  REPORT_OPEN, ReportFileName );
            if ( Form1->PSI_mode )
                print_message( MSG_TYPE_RPRT_WR_DT_TIME, RPRT_PSI );
            else
                print_message( MSG_TYPE_RPRT_WR_DT_TIME, RPRT_DBG );

            print_message( MSG_TYPE_RPRT_WR, RPRT_STAND, Form1->ComboBox1->Text.c_str() );
            print_message( MSG_TYPE_RPRT_WR, RPRT_NAME, Form1->ComboBox2->Text.c_str());
            print_message( MSG_TYPE_RPRT_WR, RPRT_NMBR, Form1->ComboBox3->Text.c_str());*/


}


