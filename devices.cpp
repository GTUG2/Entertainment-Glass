#include "devices.h"
#include "ui_devices.h"

Devices::Devices(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Devices)
{
    ui->setupUi(this);
    activityLog = new ActivityLog(this);
    scanThread = new QThread;
    ScanWorker *worker = new ScanWorker();
    worker->moveToThread(scanThread);

    connect(scanThread, SIGNAL(started()), worker, SLOT(start()));
    connect(worker, SIGNAL(newDeviceFound(QString,QString)), this, SLOT(addToList(QString,QString)));

    connect(ui->devices, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(setMac1(QListWidgetItem*)));
    connect(this, SIGNAL(log(QString)), activityLog, SLOT(addActivity(QString)));

    activityLog->show();
    scanThread->start();
}

void Devices::addToList(const QString &addr, const QString &name){
    ui->devices->addItem(addr + " : " + name);
    std::cout << addr.toStdString() << " : " << name.toStdString() << std::endl;
}

void Devices::setMac1(QListWidgetItem *addr){
    ui->mac1->setText(addr->text().split(" ")[0]);
    emit log(QString("mac1 set to: " + addr->text()));
}

Devices::~Devices()
{
    delete ui;
}
