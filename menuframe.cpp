#include "menuframe.h"
#include "ui_menuframe.h"

MenuFrame::MenuFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::MenuFrame)
{
    ui->setupUi(this);
    ui->label->setStyleSheet("image: url(://images/menu/xox.png)");
}

MenuFrame::~MenuFrame()
{
    delete ui;
}

void MenuFrame::packetReceived(packet p, int i)
{
    emit log("menu packet received");
    switch (p.app_id) {
    case 0:
        switch (p.data.menu.currentItem) {
        case 1:
            ui->label->setStyleSheet("image: url(://images/menu/xox.png)");
            break;
        case 2:
            ui->label->setStyleSheet("image: url(://images/menu/c4.png)");
            break;
        case 3:
            ui->label->setStyleSheet("image: url(://images/menu/pingboss.png)");
            break;
        case 4:
            ui->label->setText("Adam Asmaca");
            break;
        case 5:
            ui->label->setText("Taiko");
            break;
        default:
            ui->label->setText("Erkan Hoca");
            break;
        }

        if(p.data.menu.isSelected == 1){
            // send message menus to the clients
            packet m6 = {127, 6, p.data.menu.currentItem}, m7 = {127, 7, p.data.menu.currentItem};
            if(i == 1){
                emit menuMessageP1(6, "Rakip bekleniyor...");
                emit menuMessageP2(7, "Oyuncu 1 "+ ui->label->text() + " oyununu oynamak istiyor.");
                changeUIRequest(6);
                emit bl1SendData(m6);
                emit bl2SendData(m7);
            }else if(i == 2){
                emit menuMessageP2(6, "Rakip bekleniyor...");
                emit menuMessageP1(7, "Oyuncu 2 "+ ui->label->text() + " oyununu oynamak istiyor.");
                changeUIRequest(7);
                emit bl1SendData(m7);
                emit bl2SendData(m6);
            }

        }
        break;
    default:
        break;
    }
}
