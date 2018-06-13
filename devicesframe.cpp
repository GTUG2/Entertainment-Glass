#include "devicesframe.h"
#include "ui_devicesframe.h"

DevicesFrame::DevicesFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DevicesFrame)
{
    ui->setupUi(this);

    /*agent = new QBluetoothDeviceDiscoveryAgent();
    connect(agent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(newDeviceFound(QBluetoothDeviceInfo)));

    connect(ui->devices, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(itemClicked(QListWidgetItem*)));
    agent->start();*/
}

DevicesFrame::~DevicesFrame()
{
    delete ui;
}

void DevicesFrame::newDeviceFound(QBluetoothDeviceInfo info)
{
    ui->devices->addItem(info.address().toString() + " : " + info.name());
}

void DevicesFrame::itemClicked(QListWidgetItem *item)
{
    QStringList qsl = item->text().split(" : ", QString::SkipEmptyParts);
    qDebug() << qsl;
    emit deviceSelected(qsl[0], qsl[1]);
}

void DevicesFrame::cancelSearch()
{
    //agent->stop();
}
