#ifndef DEVICES_H
#define DEVICES_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QThread>
#include <iostream>
#include "rfcomm.h"
#include "scanworker.h"
#include "activitylog.h"

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
    void addToList(const QString &addr, const QString &name);
    void setMac1(QListWidgetItem *addr);
    void connectButtonClicked(bool checked = false);
    void bl1Connected();
    void bl1Cleaned(const QString &out);
    void bl1Failed(int code);

signals:
    void log(const QString &msg);
    void bl1Connect(const QString &dev, const QString &addr);
private:
    Ui::Devices *ui;
    ActivityLog *activityLog;
    QThread *scanThread;
    RFComm *bl1, *bl2;
};

#endif // DEVICES_H
