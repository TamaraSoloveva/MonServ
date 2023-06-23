#include "script.h"

 DbgClass::DbgClass(const QString &name, const QMap<QString, useFields> &cmdMap) : qFile(name), mCmd(cmdMap) {
     qFile.open(QIODevice::ReadOnly);
     if (!qFile.isOpen())
         throw std::runtime_error("unable to open dbg-file");
 }

 DbgClass::~DbgClass() {
     if (qFile.isOpen())
         qFile.close();
 }

 QVector<QVector<QString>> DbgClass::showTable() {
     QTextStream inDbg(&qFile);
     inDbg.setCodec("utf8");
     inDbg.setCodec("windows-1251");
     while(!inDbg.atEnd()) {
          QString line = inDbg.readLine();
          if (line == "DbgF")
              //DbgF - строка, определяющая версию сценария, будет использовано для поддержки обратной совсемстимости
              continue;
          linesToRunAndShow.push_back(formVector(line));
     }
     return linesToRunAndShow;
 }

QVector<QString> DbgClass::formVector( const QString &str) {
     QVector<QString>tmpV;
     tmpV.clear();
     lineVec.clear();
     if( str.size() == 0) {
         for (auto i=0; i<4; ++i)
             tmpV.push_back(" ");
     }
     else {
         QString tmp = nullptr;
         uint16_t cntr=0;
         for ( auto ch : str) {
             if (ch != ' ' )
                 tmp += ch;
             else
                 if (cntr == 2) {
                     //в старой версии dbg-файла слова разделены тремя пробелами
                     //в tmpV набираем отдельные слова из которых состоит строка.
                     //на данный момент гарантируется, что слов будет ровно 4, так как пути к файлу не содержат пробелов
                     tmpV.push_back(tmp);
                     tmp.clear();
                     cntr=0;
                     if (ch == '%')
                         break;
                 }
                 else
                     cntr++;
         }
        //пока комментарии в вектор ложаться так
        tmpV.push_back(" ");

         QMap<QString, useFields>::iterator it=nullptr;
         it = mCmd.find(tmpV.at(0));
         if (it != mCmd.end()) {
             lineVec.push_back(it.value().fullName);
             //в будущем будет использовано для проверки правильного синтаксиса
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
             //если команда не найдена, пусть будет пустая строка
             for (auto i=0; i<4; ++i)
                 lineVec.push_back(" ");
         }
       }
      return lineVec;
 }













