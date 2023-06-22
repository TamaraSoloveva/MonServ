#include "script.h"

#include <QDebug>
#include <QChar>
#include <sstream>


void Script::fOpenButton() {
    std::ifstream inDbg;
    inDbg.open(dbgName.toStdString().c_str());


    std::string line;
    while (std::getline(inDbg, line)) {
     //   qDebug() << QString::fromStdString(line) << "\n";
        if (line == "DbgF")
            continue;
        formVector(line);


    }

    emit addLine(v);
}


void Script::formVector( const std::string &str) {
    QVector<QString>tmpV;
    tmpV.clear();
    if( str.size() == 0) {
        for (auto i=0; i<4; ++i)
            tmpV.push_back(" ");
    }
    else {
        QString aaa = QString::fromStdString(str);
        const char* const space=" ";
        QString tmp = nullptr;
        uint16_t cntr=0;
        uint16_t fNum = 0;
        QMap<QString, useFields>::iterator it=nullptr;
        for ( auto ch : aaa) {
            if (ch != ' ')
                tmp += ch;
            else {
                if (cntr == 2) {
               //     qDebug() << tmp << " ";
                    tmpV.push_back(tmp);
                    tmp.clear();
                    cntr=0;
                }
                else
                    cntr++;
            }
        }

        it = mCmd.find(tmpV.at(0));
        if (it != mCmd.end()) {
            lineVec.push_back(it.value().fullName);
            qDebug() << it.value().fullName;

            if (it.value().addrField && it.value().dataField && it.value().commField && (tmpV.size() == 4)) { //111
                lineVec.push_back(tmpV.at(1));
                lineVec.push_back(tmpV.at(2));
                lineVec.push_back(tmpV.at(3));
            }
            else if(!it.value().addrField && it.value().dataField && it.value().commField  && (tmpV.size() == 3)) { //011
                lineVec.push_back(" " );
                lineVec.push_back(tmpV.at(1));
                lineVec.push_back(tmpV.at(2));
            }
            else if(it.value().addrField && !it.value().dataField && it.value().commField  && (tmpV.size() == 3)) { //101
                lineVec.push_back(tmpV.at(1) );
                lineVec.push_back(" ");
                lineVec.push_back(tmpV.at(2));
            }
            else if(!it.value().addrField && !it.value().dataField && it.value().commField && (tmpV.size() == 2)) { //001
                lineVec.push_back(" " );
                lineVec.push_back(" ");
                lineVec.push_back(tmpV.at(1));
            }
        }
        else {
            qDebug() << "err\n"   ;
        }
      }

        v.push_back(tmpV);


}


void Script::createCmdMap() {
    mCmd.insert("j", useFields("Jump", 1, 0, 1));
    mCmd.insert("to", useFields("Text Out", 0, 0, 1));
    mCmd.insert("ja", useFields("Jump To Address", 1, 1, 1));
    mCmd.insert("cl", useFields("Call", 1, 0, 1));
    mCmd.insert("r", useFields("Ret", 0, 0, 1));
    mCmd.insert("lf", useFields("Load File", 1, 1, 1));
    mCmd.insert("mw", useFields("Memory Write", 1, 1, 1));


}
