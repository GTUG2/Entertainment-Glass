#ifndef DEVICES_H
#define DEVICES_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QThread>
#include <QBluetoothSocket>
#include <QBluetoothDeviceDiscoveryAgent>
#include <iostream>
#include "activitylog.h"
#include "common.h"
#include "reader.h"
#include "xox.h"

namespace Ui {
class Devices;
}

class Devices : public QMainWindow
{
    Q_OBJECT

public:
    explicit Devices(QWidget *parent = 0);
    ~Devices();

public slots:
    void setMac1(QListWidgetItem *addr);
    void setMac2(QListWidgetItem *addr);
    void connectButtonClicked(bool checked);
    void newDeviceFound(QBluetoothDeviceInfo info);
    void blConnected();
    void bl2Connected();
    void blError(QBluetoothSocket::SocketError);
signals:
    void log(const QString &msg);
private slots:
    void on_refreshButton_clicked(bool checked);

    void on_clearButton_clicked(bool checked);
    void re();

private:
    Ui::Devices *ui;
    ActivityLog *activityLog;
    QBluetoothDeviceDiscoveryAgent *agent;
    QBluetoothSocket *bl1, *bl2;
    Reader *readerbl1;
    XOX *xox;
};

#endif // DEVICES_H
