#ifndef DEVICESFRAME_H
#define DEVICESFRAME_H

#include <QFrame>
#include <QDebug>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QListWidget>
#include <QPushButton>

namespace Ui {
class DevicesFrame;
}

class DevicesFrame : public QFrame
{
    Q_OBJECT

public:
    explicit DevicesFrame(QWidget *parent = 0);
    ~DevicesFrame();

signals:
    void deviceSelected(QString addr, QString name);

public slots:
    void newDeviceFound(QBluetoothDeviceInfo);
    void itemClicked(QListWidgetItem *item);
    void cancelSearch();
private:
    Ui::DevicesFrame *ui;
    QBluetoothDeviceDiscoveryAgent *agent;
    QPushButton *searchBtn;
};

#endif // DEVICESFRAME_H
