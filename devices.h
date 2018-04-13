#ifndef DEVICES_H
#define DEVICES_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QThread>
#include <iostream>
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

signals:
    void log(const QString &msg);
private:
    Ui::Devices *ui;
    ActivityLog *activityLog;
    QThread *scanThread;
};

#endif // DEVICES_H
