#ifndef OUTPUTCONSOLE_H
#define OUTPUTCONSOLE_H

#include <QPlainTextEdit>
#include <QMenu>


class Console : public QPlainTextEdit {
    Q_OBJECT

signals:
    void getData(const QByteArray &data);
    void signalWriteCaptureTxt( QByteArray wrDt);
    void signalWriteReport(QByteArray wrDt, bool needDt);

public:
    explicit Console(QWidget *parent = nullptr);

    void putData(const QByteArray &data);
    void putDataRus(const QByteArray &data);
    void putString (const char *data);
    void slotSetKredoMode() { isKredo=true; }
//    void setLocalEchoEnabled(bool set);

//protected:
//    void keyPressEvent(QKeyEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
//    void contextMenuEvent(QContextMenuEvent *e) override;
    //void getModCode(const QByteArray &data);

private:
    bool isKredo;
    bool m_localEchoEnabled = false;
//    QMenu *menu;

};

#endif // OUTPUTCONSOLE_H
