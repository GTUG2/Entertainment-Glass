#ifndef SERVERUI_H
#define SERVERUI_H

#include "connectframe.h"
#include "devicesframe.h"
#include "common.h"
#include "menuframe.h"
#include "reader.h"
#include "messageframe.h"
#include "xoxlogic.h"
#include "xoxframe.h"
#include "pingbossframe.h"
#include "pingbosslogic.h"

#include "connect4frame.h"
#include "connect4logic.h"
#include <QMainWindow>
#include <QBluetoothSocket>

namespace Ui {
class ServerUI;
}

class ServerUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerUI(QWidget *parent = 0);
    ~ServerUI();

    QBluetoothSocket *bl1, *bl2;
    void showMenuFrame();
    void showMessageFrame(int b1, int b2);
    void showXOXFrame(int b1, int b2);
    void showc4Frame(int b1, int b2);
    void showPBFrame(int b1, int b2);

public slots:
    void blConnect(QString addr1, QString addr2);
    void bl1Connected();
    void bl2Connected();
    void bl1Disconnected();
    void bl2Disconnected();
    void bl1Error(QBluetoothSocket::SocketError);
    void bl2Error(QBluetoothSocket::SocketError);

    void bl1DataReceived(packet);
    void bl2DataReceived(packet);
    void bl1SendData(packet);
    void bl2SendData(packet);
    void blSendData(packet);

    void log(QString msg);
    void changeUI(int);

    void setMessageP1(int,QString);
    void setMessageP2(int,QString);

private:
    Ui::ServerUI *ui;
    MenuFrame *mfp1, *mfp2;
    MessageFrame *msgp1, *msgp2;
    DevicesFrame *df;
    ConnectFrame *cf;
    Reader *readerbl1, *readerbl2;
    XOXLogic *xox_logic_ptr;
    XOXFrame *xoxf1, *xoxf2;
    connect4frame *c4f1, *c4f2;
    connect4logic *c4logicptr;
    PingBossFrame *pbf1, *pbf2;
    PingBossLogic *pbl;

    int bl1target, bl2target;
    int cc = 0;
};

#endif // SERVERUI_H
