#include "devices.h"
#include "ui_devices.h"

Devices::Devices(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Devices)
{
    agent = new QBluetoothDeviceDiscoveryAgent;
    bl1 = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    bl2 = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    ui->setupUi(this);
    activityLog = new ActivityLog(this);
    xox = new XOX(this);
    readerbl1 = new Reader(this);

    connect(ui->devices, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(setMac1(QListWidgetItem*)));
    connect(ui->devices, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(setMac2(QListWidgetItem*)));
    connect(this, SIGNAL(log(QString)), activityLog, SLOT(addActivity(QString)));

    connect(ui->connectButton, SIGNAL(clicked(bool)), this, SLOT(connectButtonClicked(bool)));
    connect(agent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(newDeviceFound(QBluetoothDeviceInfo)));

    xox->show();
    agent->start();
    activityLog->show();
}

void Devices::newDeviceFound(QBluetoothDeviceInfo info){
    ui->devices->addItem(new QListWidgetItem(info.address().toString() + " : " + info.name()));
    log("Device found: " + info.address().toString() + " : " + info.name());
    qDebug() << "found";
}

void Devices::setMac1(QListWidgetItem *addr){
    ui->mac1->setText(addr->text().split(" ")[0]);
    emit log(QString("mac1 set to: " + addr->text()));
}

void Devices::setMac2(QListWidgetItem *addr){
    ui->mac2->setText(addr->text().split(" ")[0]);
    emit log(QString("mac2 set to: " + addr->text()));
}

void Devices::connectButtonClicked(bool checked){
    bl1->connectToService(QBluetoothAddress(ui->mac1->text()), QBluetoothUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB")), QIODevice::ReadWrite);
    bl2->connectToService(QBluetoothAddress(ui->mac2->text()), QBluetoothUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB")), QIODevice::ReadWrite);
    connect(bl1, SIGNAL(connected()), this, SLOT(blConnected()));
    connect(bl2, SIGNAL(connected()), this, SLOT(bl2Connected()));
    connect(bl1, SIGNAL(error(QBluetoothSocket::SocketError)), this, SLOT(blError(QBluetoothSocket::SocketError)));
    connect(bl2, SIGNAL(error(QBluetoothSocket::SocketError)), this, SLOT(blError(QBluetoothSocket::SocketError)));
    connect(readerbl1, SIGNAL(onpacketreceived(packet)), xox, SLOT(onBoardChange(packet)));
}

void Devices::blConnected(){
    log("blConnected");
    readerbl1->setup(bl1);
    connect(bl1, SIGNAL(readyRead()), readerbl1, SLOT(readready()));
    //connect(bl1, SIGNAL(readyRead()), this, SLOT(re()));
}

void Devices::bl2Connected(){
    log("bl2Connected");
}

void Devices::blError(QBluetoothSocket::SocketError err){
    log("blError");
}

Devices::~Devices()
{
    delete ui;
}

void Devices::on_refreshButton_clicked(bool checked)
{QByteArray b1, b2;
    b1.append("bl1: ").append(ui->lineEdit->text());
    b2.append("bl2: ").append(ui->lineEdit->text());
    bl1->write(b1);
    bl2->write(b2);
}

void Devices::on_clearButton_clicked(bool checked)
{
    //bl1->write("q");
    //bl2->write("q");

}

void Devices::re(){
    QByteArray qbt = bl1->read(32);
    qDebug() << "read bytes:" << qbt.toHex();
}
