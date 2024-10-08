#include "outputConsole.h"

#include "outputConsole.h"
#include <QtCore/QDebug>
#include <QTextCodec>

#include <QScrollBar>

Console::Console(QWidget *parent) :
    QPlainTextEdit(parent)
{
    document()->setMaximumBlockCount(100000);
    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::white);
    p.setColor(QPalette::Text, Qt::black);
    setPalette(p);
    isKredo=false;
}


void Console::putData(const QByteArray &data)
{
    emit signalWriteCaptureTxt(data);
    emit signalWriteReport(data, false);
    QTextCodec *codec = QTextCodec::codecForName("cp1251");
    QString a = codec->toUnicode(data);
    insertPlainText(a);
    QScrollBar *bar = verticalScrollBar();
    bar->setValue(bar->maximum());
}

void Console::putDataRus(const QByteArray &data)
{
    emit signalWriteCaptureTxt(data);
    emit signalWriteReport(data, false);
    QTextCodec *codec = QTextCodec::codecForName("cp866");
    QString a = codec->toUnicode(data);
    insertPlainText(a);
    QScrollBar *bar = verticalScrollBar();
    bar->setValue(bar->maximum());
}


void Console::putString (const char *data)
{

    QString str = QString(data);
    setPlainText(str);
    //insertPlainText(data);
    QScrollBar *bar = verticalScrollBar();
    bar->setValue(bar->maximum());
}


//void Console::setLocalEchoEnabled(bool set)
//{
//    m_localEchoEnabled = set;
//}

//void Console::keyPressEvent(QKeyEvent *e)
//{
////    if ((e->key() >= 0x20) && (e->key() <= 0x70))


//    switch (e->key()) {
//    case Qt::Key_Backspace:
//    case Qt::Key_Left:
//    case Qt::Key_Right:
//    case Qt::Key_Up:
//    case Qt::Key_Down:
//        break;
//    default:
//        if (m_localEchoEnabled)
//            QPlainTextEdit::keyPressEvent(e);
//        emit getData(e->text().toLocal8Bit());
//    }
//}

void Console::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    setFocus();
}

void Console::mouseMoveEvent(QMouseEvent *e){
    Q_UNUSED(e)
//      qDebug()<< "AAAA";
    //Console::mouseMoveEvent( QMouseEvent *e);


}

void Console::mouseDoubleClickEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
}

//void Console::contextMenuEvent(QContextMenuEvent *e)
//{
//    Q_UNUSED(e)
    //QMenu *menu = createStandardContextMenu();
//    QMenu m2;
//    QAction *a1 = m2.addAction("Delete");


//    QAction *selectedAction = m2.exec(e->globalPos());
    //delete menu;
//}
