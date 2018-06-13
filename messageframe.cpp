#include "messageframe.h"
#include "ui_messageframe.h"

MessageFrame::MessageFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::MessageFrame)
{
    ui->setupUi(this);
}

MessageFrame::~MessageFrame()
{
    delete ui;
}

void MessageFrame::packetReceived(packet p, int i)
{
    switch (p.app_id) {
    case 0:
        switch (p.data.menu.currentItem) {
        case 1:
            if(i == 1){
                showMessage(1, "bekle");
            }else if(i == 2){
                showMessage(1, "cevap ver");
            }
            break;
        default:
            break;
        }
        break;
    case 7:
        switch (p.data.menu._cursor) {
        case 1: // reddet
            ui->ok->setChecked(true);
            ui->cancel->setChecked(false);
            break;
        case 2: // kabul et
            ui->ok->setChecked(false);
            ui->cancel->setChecked(true);
            break;
        default:
            break;
        }

        emit blSendData(p);
        if(p.data.menu.isAccepted == 1){
            emit changeUIRequest(p.data.menu.currentItem);
        }else if(p.data.menu.isAccepted == 2){
            emit changeUIRequest(0);
        }
        break;
    case 6:
        break;
    case 9:

        break;
    case 10:

        break;
    case 11:

        break;
    case 99:
        emit blSendData(p);
        changeUIRequest(0);
        qDebug() << "RESET REQUEST RECEIVED";
        break;
    default:
        qDebug() << "[MESSAGEFRAME]Unkown appid: " << p.app_id;
        break;
    }
}

void MessageFrame::showMessage(int type, QString message)
{
    switch (type) {
    case 6:
        ui->title->setText("Oyun İsteği");
        ui->ok->setVisible(false);
        ui->cancel->setVisible(false);
        break;
    case 7:
        ui->title->setText("Oyun İsteği");
        ui->ok->setVisible(true);
        ui->cancel->setVisible(true);
        break;
    case 9:
        ui->title->setText("Oyun Sonucu");
        ui->ok->setVisible(false);
        ui->cancel->setVisible(false);
        break;
    case 10:
        ui->title->setText("Oyun Sonucu");
        ui->ok->setVisible(false);
        ui->cancel->setVisible(false);
        break;
    case 11:
        ui->title->setText("Oyun Sonucu");
        ui->ok->setVisible(false);
        ui->cancel->setVisible(false);
        break;
    }
    ui->message->setText(message);
    ui->message->setVisible(true);
}
