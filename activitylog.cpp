#include "activitylog.h"
#include "ui_activitylog.h"
//taalai
ActivityLog::ActivityLog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ActivityLog)
{
    ui->setupUi(this);
}

ActivityLog::~ActivityLog()
{
    delete ui;
}

void ActivityLog::addActivity(const QString &msg){
    ui->listWidget->addItem(msg);
}
