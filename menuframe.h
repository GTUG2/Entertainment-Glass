#ifndef MENUFRAME_H
#define MENUFRAME_H

#include "common.h"

#include <QFrame>

namespace Ui {
class MenuFrame;
}

class MenuFrame : public QFrame
{
    Q_OBJECT

public:
    explicit MenuFrame(QWidget *parent = 0);
    ~MenuFrame();

signals:
    void log(QString);
    void changeUIRequest(int);
    void bl1SendData(packet);
    void bl2SendData(packet);
    void blSendData(packet);
    void menuMessageP1(int, QString);
    void menuMessageP2(int, QString);

public slots:
    void packetReceived(packet, int i);

private:
    Ui::MenuFrame *ui;
};

#endif // MENUFRAME_H
