#include "connectframe.h"
#include "ui_connectframe.h"

ConnectFrame::ConnectFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ConnectFrame)
{
    ui->setupUi(this);
}

ConnectFrame::~ConnectFrame()
{
    delete ui;
}

void ConnectFrame::setDevice(QString addr, QString name)
{
    if(ui->bl1addr->text().compare("Mac Address 1") == 0){
        ui->bl1name->setText(name);
        ui->bl1name->setStyleSheet("color: rgb(0, 0, 0);");
        ui->bl1addr->setText(addr);
        ui->bl1clear->setStyleSheet("border-color: rgba(11, 104, 81, 202);\ncolor: rgb(238, 238, 236);\nbackground-color: rgb(227, 136, 0); border: none;");
    } else if(ui->bl2addr->text().compare("Mac Address 2") == 0){
        ui->bl2name->setText(name);
        ui->bl2name->setStyleSheet("color: rgb(0, 0, 0);");
        ui->bl2addr->setText(addr);
        ui->bl2clear->setStyleSheet("border-color: rgba(11, 104, 81, 202);\ncolor: rgb(238, 238, 236);\nbackground-color: rgb(227, 136, 0); border: none;");
    }

    if(ui->bl1addr->text().compare("Mac Address 1") != 0 && ui->bl2addr->text().compare("Mac Address 2") != 0){
        ui->connect->setStyleSheet("background-color: rgb(13, 126, 91); color: rgb(238, 238, 236); border: none;");
    }
}

void ConnectFrame::on_bl1clear_clicked()
{
    ui->bl1name->setText("Bluetooth 1");
    ui->bl1name->setStyleSheet("color: rgb(136, 138, 133);");
    ui->bl1addr->setText("Mac Address 1");
    ui->bl1clear->setStyleSheet("background-color: rgb(136, 138, 133); border: none;");
    ui->connect->setStyleSheet("background-color: rgb(136, 138, 133); border: none;");
}

void ConnectFrame::on_bl2clear_clicked()
{
    ui->bl2name->setText("Bluetooth 2");
    ui->bl2name->setStyleSheet("color: rgb(136, 138, 133);");
    ui->bl2addr->setText("Mac Address 2");
    ui->bl2clear->setStyleSheet("background-color: rgb(136, 138, 133); border: none;");
    ui->connect->setStyleSheet("background-color: rgb(136, 138, 133); border: none;");
}

void ConnectFrame::on_connect_clicked()
{
    if(ui->bl2addr->text().compare("Mac Address 2") != 0 && ui->bl1addr->text().compare("Mac Address 1") != 0){
        emit bluetoothConnect(ui->bl1addr->text(), ui->bl2addr->text());
    }
}
