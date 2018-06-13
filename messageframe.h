#ifndef MESSAGEFRAME_H
#define MESSAGEFRAME_H

#include "common.h"

#include <QFrame>
#include <QDebug>

namespace Ui {
class MessageFrame;
}

class MessageFrame : public QFrame
{
    Q_OBJECT

public:
    explicit MessageFrame(QWidget *parent = 0);
    ~MessageFrame();

signals:
    void changeUIRequest(int);
    void bl1SendData(packet);
    void bl2SendData(packet);
    void blSendData(packet);

public slots:
    void showMessage(int type, QString message);
    void packetReceived(packet, int);

private:
    Ui::MessageFrame *ui;
    int cancelUI, okUI;
};

#endif // MESSAGEFRAME_H
