#include "serverui.h"
#include <QDebug>
#include <QMediaPlayer>
#include "ui_serverui.h"

ServerUI::ServerUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServerUI)
{
    ui->setupUi(this);
    mfp1 = new MenuFrame(ui->p1);
    mfp2 = new MenuFrame(ui->p2);
    mfp1->setVisible(false);
    mfp2->setVisible(false);
    msgp1 = new MessageFrame(ui->p1);
    msgp2 = new MessageFrame(ui->p2);
    msgp1->setVisible(false);
    msgp2->setVisible(false);
    df = new DevicesFrame(ui->p1);
    cf = new ConnectFrame(ui->p2);
    bl1 = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    bl2 = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    readerbl1 = new Reader(this);
    readerbl2 = new Reader(this);
    xox_logic_ptr = new XOXLogic(this, (QHBoxLayout*)ui->gameStatus->layout());
    xoxf1 = new XOXFrame(ui->p1);
    xoxf2 = new XOXFrame(ui->p2);
    xoxf1->setVisible(false);
    xoxf2->setVisible(false);
    c4logicptr = new connect4logic(this, (QHBoxLayout*)ui->gameStatus->layout());
    c4f1 = new connect4frame(c4logicptr, ui->p1);
    c4f2 = new connect4frame(c4logicptr, ui->p2);
    c4f1->setVisible(false);
    c4f2->setVisible(false);

    pbf1 = new PingBossFrame(ui->p1);
    pbf2 = new PingBossFrame(ui->p2);
    pbl = new PingBossLogic(this, (QHBoxLayout*)ui->gameStatus->layout());
    pbf1->setVisible(false);
    pbf2->setVisible(false);

    connect(df, SIGNAL(deviceSelected(QString,QString)), cf, SLOT(setDevice(QString,QString)));
    connect(cf, SIGNAL(bluetoothConnect(QString,QString)), this, SLOT(blConnect(QString,QString)));

    // Bluetooth SIGNALS
    connect(bl1, SIGNAL(connected()), this, SLOT(bl1Connected()));
    connect(bl2, SIGNAL(connected()), this, SLOT(bl2Connected()));
    connect(bl1, SIGNAL(error(QBluetoothSocket::SocketError)), this, SLOT(bl1Error(QBluetoothSocket::SocketError)));
    connect(bl2, SIGNAL(error(QBluetoothSocket::SocketError)), this, SLOT(bl2Error(QBluetoothSocket::SocketError)));
    connect(bl1, SIGNAL(readyRead()), readerbl1, SLOT(readready()));
    connect(bl2, SIGNAL(readyRead()), readerbl2, SLOT(readready()));
    connect(readerbl1, SIGNAL(onpacketreceived(packet)), this, SLOT(bl1DataReceived(packet)));
    connect(readerbl2, SIGNAL(onpacketreceived(packet)), this, SLOT(bl2DataReceived(packet)));

    // Menu Frame SIGNALS
    connect(mfp1, SIGNAL(log(QString)), this, SLOT(log(QString)));
    connect(mfp2, SIGNAL(log(QString)), this, SLOT(log(QString)));
    connect(mfp1, SIGNAL(bl1SendData(packet)), this, SLOT(bl1SendData(packet)));
    connect(mfp2, SIGNAL(bl1SendData(packet)), this, SLOT(bl1SendData(packet)));
    connect(mfp1, SIGNAL(bl2SendData(packet)), this, SLOT(bl2SendData(packet)));
    connect(mfp2, SIGNAL(bl2SendData(packet)), this, SLOT(bl2SendData(packet)));
    connect(mfp1, SIGNAL(blSendData(packet)), this, SLOT(blSendData(packet)));
    connect(mfp2, SIGNAL(blSendData(packet)), this, SLOT(blSendData(packet)));
    connect(mfp1, SIGNAL(changeUIRequest(int)), this, SLOT(changeUI(int)));
    connect(mfp2, SIGNAL(changeUIRequest(int)), this, SLOT(changeUI(int)));
    connect(mfp1, SIGNAL(menuMessageP1(int,QString)), this, SLOT(setMessageP1(int,QString)));
    connect(mfp2, SIGNAL(menuMessageP1(int,QString)), this, SLOT(setMessageP1(int,QString)));
    connect(mfp1, SIGNAL(menuMessageP2(int,QString)), this, SLOT(setMessageP2(int,QString)));
    connect(mfp2, SIGNAL(menuMessageP2(int,QString)), this, SLOT(setMessageP2(int,QString)));

    // Message Frame SIGNALS
    connect(msgp1, SIGNAL(changeUIRequest(int)), this, SLOT(changeUI(int)));
    connect(msgp2, SIGNAL(changeUIRequest(int)), this, SLOT(changeUI(int)));
    connect(msgp1, SIGNAL(bl1SendData(packet)), this, SLOT(bl1SendData(packet)));
    connect(msgp2, SIGNAL(bl2SendData(packet)), this, SLOT(bl2SendData(packet)));
    connect(msgp1, SIGNAL(blSendData(packet)), this, SLOT(blSendData(packet)));
    connect(msgp2, SIGNAL(blSendData(packet)), this, SLOT(blSendData(packet)));

    //XOX Logic Signals
    connect(xox_logic_ptr, SIGNAL(bl1SendData(packet)), this, SLOT(bl1SendData(packet)));
    connect(xox_logic_ptr, SIGNAL(bl2SendData(packet)), this, SLOT(bl2SendData(packet)));
    connect(xox_logic_ptr, SIGNAL(blSendData(packet)), this, SLOT(blSendData(packet)));
    connect(xox_logic_ptr, SIGNAL(changeUIRequest(int)), this, SLOT(changeUI(int)));
    connect(xox_logic_ptr, SIGNAL(ui1Update(xox)), xoxf1, SLOT(updateUI(xox)));
    connect(xox_logic_ptr, SIGNAL(ui2Update(xox)), xoxf2, SLOT(updateUI(xox)));
    connect(xox_logic_ptr, SIGNAL(uiReset()), xoxf1, SLOT(resetUI()));
    connect(xox_logic_ptr, SIGNAL(uiReset()), xoxf2, SLOT(resetUI()));
    connect(xox_logic_ptr, SIGNAL(p1Message(int,QString)), this, SLOT(setMessageP1(int,QString)));
    connect(xox_logic_ptr, SIGNAL(p2Message(int,QString)), this, SLOT(setMessageP2(int,QString)));

    //Connect 4 Logic Signals
    connect(c4logicptr, SIGNAL(bl1SendData(packet)), this, SLOT(bl1SendData(packet)));
    connect(c4logicptr, SIGNAL(bl2SendData(packet)), this, SLOT(bl2SendData(packet)));
    connect(c4logicptr, SIGNAL(blSendData(packet)), this, SLOT(blSendData(packet)));
    connect(c4logicptr, SIGNAL(changeUIRequest(int)), this, SLOT(changeUI(int)));
    connect(c4logicptr, SIGNAL(ui2Update()), c4f2, SLOT(updateUi()));
    connect(c4logicptr, SIGNAL(ui1Update()), c4f1, SLOT(updateUi()));
    connect(c4logicptr, SIGNAL(p1Message(int,QString)), this, SLOT(setMessageP1(int,QString)));
    connect(c4logicptr, SIGNAL(p2Message(int,QString)), this, SLOT(setMessageP2(int,QString)));

    //PingBoss Logic Signals
    connect(pbl, SIGNAL(bl1SendData(packet)), this, SLOT(bl1SendData(packet)));
    connect(pbl, SIGNAL(bl2SendData(packet)), this, SLOT(bl2SendData(packet)));
    connect(pbl, SIGNAL(blSendData(packet)), this, SLOT(blSendData(packet)));
    connect(pbl, SIGNAL(changeUIRequest(int)), this, SLOT(changeUI(int)));
    connect(pbl, SIGNAL(ui1Update(pingboss)), pbf1, SLOT(updateUI(pingboss)));
    connect(pbl, SIGNAL(ui2Update(pingboss)), pbf2, SLOT(updateUI(pingboss)));
    connect(pbl, SIGNAL(uiReset()), pbf1, SLOT(resetUI()));
    connect(pbl, SIGNAL(uiReset()), pbf2, SLOT(resetUI()));
    connect(pbl, SIGNAL(p1Message(int,QString)), this, SLOT(setMessageP1(int,QString)));
    connect(pbl, SIGNAL(p2Message(int,QString)), this, SLOT(setMessageP2(int,QString)));
}

ServerUI::~ServerUI()
{
    delete ui;
}

void ServerUI::blConnect(QString addr1, QString addr2)
{
    //emit df->cancelSearch();
    bl1->connectToService(QBluetoothAddress(addr1), QBluetoothUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB")), QIODevice::ReadWrite);
    bl2->connectToService(QBluetoothAddress(addr2), QBluetoothUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB")), QIODevice::ReadWrite);
}

void ServerUI::bl1Connected()
{
    packet p1, p2;
    memset(&p1, 0, sizeof(p1));
    memset(&p2, 0, sizeof(p1));
    p1.start = 127;
    p2.start = 127;
    p1.app_id = 8;
    p2.app_id = 8;
    p1.data.initial.playerId = 1;
    p2.data.initial.playerId = 2;
    emit log("bl1 connected");
    readerbl1->setup(bl1);
    if(++cc == 2){
        emit showMenuFrame();
        bl1SendData(p1);
        bl2SendData(p2);
        qDebug() << "Initial data sent";
    }
}

void ServerUI::bl2Connected()
{
    packet p1, p2;
    memset(&p1, 0, sizeof(p1));
    memset(&p2, 0, sizeof(p1));
    p1.start = 127;
    p2.start = 127;
    p1.app_id = 8;
    p2.app_id = 8;
    p1.data.initial.playerId = 1;
    p2.data.initial.playerId = 2;
    emit log("bl2 connected");
    readerbl2->setup(bl2);
    if(++cc == 2){
        emit showMenuFrame();
        bl1SendData(p1);
        bl2SendData(p2);
        qDebug() << "Initial data sent";
    }
}

void ServerUI::bl1Disconnected()
{
    emit log("bl1 disconnected");
    --cc;
}

void ServerUI::bl2Disconnected()
{
    emit log("bl2 disconnected");
    --cc;
}

void ServerUI::bl1Error(QBluetoothSocket::SocketError)
{
    emit log("bl1 error");
}

void ServerUI::bl2Error(QBluetoothSocket::SocketError)
{
    emit log("bl2 error");
}

void ServerUI::bl1DataReceived(packet p)
{
    QString dbg;
    for(unsigned int i = 0 ; i < sizeof(p) ; ++i){
        dbg.append(QString::number(*((char *)&p + i))).append(" ");
    }
    qDebug() << "bl1: " << dbg;
    emit log("bl1 data received");
    switch (bl1target) {
    case 0:
        mfp1->packetReceived(p, 1);
        break;
    case 1:
        xox_logic_ptr->packetReceived(p, 1);
        break;
    case 2:
        c4logicptr->packetReceived(p,1);
        break;
    case 3:
        pbl->packetReceived(p,1);
        break;
    case 6:
        msgp1->packetReceived(p, 1);
        break;
    case 7:
        msgp1->packetReceived(p, 1);
        break;
    case 9:
        msgp1->packetReceived(p, 1);
        break;
    case 10:
        msgp1->packetReceived(p, 1);
        break;
    case 11:
        msgp1->packetReceived(p, 1);
        break;
    default:
        // case 6 is empty, no possible data
        break;
    }
}

void ServerUI::bl2DataReceived(packet p)
{
    QString dbg;
    for(unsigned int i = 0 ; i < sizeof(p) ; ++i){
        dbg.append(QString::number(*((char *)&p + i))).append(" ");
    }
    qDebug() << "bl2: " << dbg;
    emit log("bl2 data received");
    switch (bl2target) {
    case 0:
        mfp2->packetReceived(p, 2);
        break;
    case 1:
        xox_logic_ptr->packetReceived(p, 2);
        break;
    case 2:
        c4logicptr->packetReceived(p, 2);
        break;
    case 3:
        pbl->packetReceived(p,2);
        break;
    case 6:
        msgp2->packetReceived(p, 2);
        break;
    case 7:
        msgp2->packetReceived(p, 2);
        break;
    case 9:
        msgp2->packetReceived(p, 2);
        break;
    case 10:
        msgp2->packetReceived(p, 2);
        break;
    case 11:
        msgp2->packetReceived(p, 2);
        break;
    default:
        break;
    }
}

void ServerUI::log(QString msg)
{
    ui->log->addItem(msg);
}

void ServerUI::showMenuFrame()
{
    df->setVisible(false);
    cf->setVisible(false);
    mfp1->setVisible(true);
    mfp2->setVisible(true);
    msgp1->setVisible(false);
    msgp2->setVisible(false);
    xoxf1->setVisible(false);
    xoxf2->setVisible(false);
    c4f1->setVisible(false);
    c4f2->setVisible(false);
    pbf1->setVisible(false);
    pbf2->setVisible(false);
    bl1target = 0;
    bl2target = 0;
}

void ServerUI::showMessageFrame(int b1, int b2)
{
    df->setVisible(false);
    cf->setVisible(false);
    mfp1->setVisible(false);
    mfp2->setVisible(false);
    msgp1->setVisible(true);
    msgp2->setVisible(true);
    xoxf1->setVisible(false);
    xoxf2->setVisible(false);
    c4f1->setVisible(false);
    c4f2->setVisible(false);
    pbf1->setVisible(false);
    pbf2->setVisible(false);
    bl1target = b1;
    bl2target = b2;
}
void ServerUI::showXOXFrame(int b1, int b2)
{
    df->setVisible(false);
    cf->setVisible(false);
    mfp1->setVisible(false);
    mfp2->setVisible(false);
    msgp1->setVisible(false);
    msgp2->setVisible(false);
    xoxf1->setVisible(true);
    xoxf2->setVisible(true);
    c4f1->setVisible(false);
    c4f2->setVisible(false);
    pbf1->setVisible(false);
    pbf2->setVisible(false);
    xox_logic_ptr->showScoreboard();
    bl1target = b1;
    bl2target = b2;
}
void ServerUI::showc4Frame(int b1, int b2)
{
    df->setVisible(false);
    cf->setVisible(false);
    mfp1->setVisible(false);
    mfp2->setVisible(false);
    msgp1->setVisible(false);
    msgp2->setVisible(false);
    xoxf1->setVisible(false);
    xoxf2->setVisible(false);
    c4f1->setVisible(true);
    c4f2->setVisible(true);
    pbf1->setVisible(false);
    pbf2->setVisible(false);
    c4logicptr->showScoreboard();

    bl1target = b1;
    bl2target = b2;
}

void ServerUI::showPBFrame(int b1, int b2){
    df->setVisible(false);
    cf->setVisible(false);
    mfp1->setVisible(false);
    mfp2->setVisible(false);
    msgp1->setVisible(false);
    msgp2->setVisible(false);
    xoxf1->setVisible(false);
    xoxf2->setVisible(false);
    c4f1->setVisible(false);
    c4f2->setVisible(false);
    pbf1->setVisible(true);
    pbf2->setVisible(true);
    pbl->showScoreboard();

    bl1target = b1;
    bl2target = b2;
}

void ServerUI::changeUI(int ui)
{
    switch (ui) {
    case 0:
        emit showMenuFrame();
        qDebug() << "[CHANGE_UI][MAIN_MENU]";
        break;
    case 1:
        emit showXOXFrame(1,1);
        qDebug() << "[CHANGE_UI][TIC_TAC_TOE]";
        break;
    case 2:
        emit showc4Frame(2,2);
        qDebug() << "[CHANGE_UI][CONNECT4]";
        break;
    case 3:
        emit showPBFrame(3,3);
        qDebug() << "[CHANGE_UI][PING_BOSS]";
        break;
    case 4:
        qDebug() << "[CHANGE_UI][HANGMAN]";
        break;
    case 5:
        qDebug() << "[CHANGE_UI][TAIKO]";
        break;
    case 6:
        qDebug() << "[CHANGE_UI][P1-TO-P2]";
        showMessageFrame(6, 7);
        break;
    case 7:
        qDebug() << "[CHANGE_UI][P2-TO-P1]";
        showMessageFrame(7, 6);
        break;
    case 9:
        qDebug() << "[CHANGE_UI][WIN_MSG]";
        showMessageFrame(9, 10);
        break;
    case 10:
        qDebug() << "[CHANGE_UI][LOSE_MSG]";
        showMessageFrame(10, 9);
        break;
    case 11:
        qDebug() << "[CHANGE_UI][DRAW_MSG]";
        showMessageFrame(11, 11);
        break;
    default:
        qDebug() << "What kind of UI is this: "<< ui;
        break;
    }
}

void ServerUI::setMessageP1(int t, QString m)
{
    msgp1->showMessage(t,m);
}

void ServerUI::setMessageP2(int t, QString m)
{
    msgp2->showMessage(t,m);
}

void ServerUI::bl1SendData(packet p)
{
    QString dbg;
    for(unsigned int i = 0 ; i < sizeof(p) ; ++i){
        dbg.append(QString::number(*((char *)&p + i))).append(" ");
    }
    qDebug() << "bl1 sent: " << dbg;
    qint64 total = 0;
    do{
        total += bl1->write((char*)&p + total, sizeof(p) - total);
    }while(total != sizeof(p));
}

void ServerUI::bl2SendData(packet p)
{
    QString dbg;
    for(unsigned int i = 0 ; i < sizeof(p) ; ++i){
        dbg.append(QString::number(*((char *)&p + i))).append(" ");
    }
    qDebug() << "bl2 sent: " << dbg;
    qint64 total = 0;
    do{
        total += bl2->write((char*)&p + total, sizeof(p) - total);
    }while(total != sizeof(p));
}

void ServerUI::blSendData(packet p)
{
    QString dbg;
    for(unsigned int i = 0 ; i < sizeof(p) ; ++i){
        dbg.append(QString::number(*((char *)&p + i))).append(" ");
    }
    qDebug() << "bl sent: " << dbg;
    qDebug() << "sending data";
    qint64 total = 0;
    do{
        total += bl1->write((char*)&p + total, sizeof(p) - total);
    }while(total != sizeof(p));

    total = 0;
    do{
        total += bl2->write((char*)&p + total, sizeof(p) - total);
    }while(total != sizeof(p));
}
