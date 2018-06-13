#include "pingbosslogic.h"

#include <QLabel>
#include <QDebug>

PingBossLogic::PingBossLogic(QObject *parent, QHBoxLayout *container) : QObject(parent)
{
    stepper = new QTimer(this);
    srand(time(NULL));

    bossDestination = new int;
    uiStep = new int;
    p1Destination = new int;
    p2Destination = new int;
    p1Y = new int;
    p2Y = new int;
    bossY = new int;

    *bossDestination = rand()%16;
    *p1Destination = 8;
    *p2Destination = 8;
    *p1Y = 8;
    *p2Y = 8;
    *bossY = 8;
    *uiStep = 0;

    memset(bulletsX, -99, sizeof(int) * 20);
    memset(bulletsY, -1, sizeof(int) * 20);

    stepper->setSingleShot(false);
    connect(stepper, &QTimer::timeout, [=]() {
        //qDebug() << "[stepper]";
        int ui = 0;
        packet p;
        memset(&p, 0, sizeof(p));
        p.start = 127;
        p.app_id = PINGBOSS_ID;
        p.data.ping_boss.p1pos = *p1Y * 4;
        p.data.ping_boss.p2pos = *p2Y * 4;
        p.data.ping_boss.bossPos = *bossY * 4;
        p.data.ping_boss.bossHp = health->value();

        for(int i = 0 ; i < 20 ; ++i)
            if(bulletsY[i] != -1){
                bulletsX[i] += (uint8_t)0x10;
            }

        for(int i = 10 ; i < 15 ; ++i){
            if(*p1Y - bulletsY[i] < 4 && bulletsX[i] > 12){
                ui = 13;
            }
        }

        for(int i = 15 ; i < 20 ; ++i){
            if(*p2Y - bulletsY[i] < 4 && bulletsX[i] > 13){
                ui = 13;
            }
        }

        for(int i = 0 ; i < 10 ; ++i){
            if(*bossY - bulletsY[i] < 4 && bulletsX[i] > 12){
                health->setValue(health->value() - 1);
                bulletsY[i] = -1;
            } else if (bulletsX[i] > 12) {
                bulletsY[i] = -1;
            }
        }

        if(health->value() < 1){
            ui = 12;
        }

        if(ui != 0){
            memset(&p, 0, sizeof(p));
            p.start = 127;
            p.app_id = ui;
            blSendData(p);

            emit p1Message(9, "Tebrikler kazandın.");
            emit p2Message(9, "Tebrikler kazandın.");
            emit changeUIRequest(9);
            scoreboard->setVisible(false);
            resetALL();
            stepper->stop();
            uiUpdater->stop();

            QTimer *selfDestruct = new QTimer();

            selfDestruct->setSingleShot(true);
            connect(selfDestruct, &QTimer::timeout, [=](){
                packet p;
                memset(&p, 0, sizeof(p));
                p.start = 127;
                p.app_id = 0;
                selfDestruct->deleteLater();
                changeUIRequest(0);
                blSendData(p);
                resetVariables();
            });

            selfDestruct->start(4000);
        }

        for(int i = 0 ; i < 5 ; ++i){
            p.data.ping_boss.p1Bullets[i] = ((bulletsX[i] & 0x0F) << 4) | (bulletsY[i] & 0x0F);
            p.data.ping_boss.p2Bullets[i+5] = ((bulletsX[i+5] & 0x0F) << 4) | (bulletsY[i+5] & 0x0F);
        }

        for(int i = 0 ; i < 10 ; ++i){
            p.data.ping_boss.bossBullets[i+10] = (bulletsX[i+10] & 0x0F) | (bulletsY[i+10] & 0x0F);
        }

        blSendData(p);
        if(*bossY == *bossDestination)
            *bossDestination = 3 + rand()%11;
    });

    uiUpdater = new QTimer();

    connect(uiUpdater, &QTimer::timeout, [=](){
        qDebug() << "[ui update]";
        if(*uiStep == 3){
            if(*p1Y < *p1Destination)
                *p1Y += 1;
            else if(*p1Y > *p1Destination)
                *p1Y -= 1;

            if(*p2Y < *p2Destination)
                *p2Y += 1;
            else if(*p2Y > *p2Destination)
                *p2Y -= 1;

            if(*bossY < *bossDestination)
                *bossY += 1;
            else if(*bossY > *bossDestination)
                *bossY -= 1;

            *uiStep = 0;
        }
        *uiStep = *uiStep + 1;

        pingboss pb;

        memset(&pb, 0, sizeof(pb));
        if(*p1Y < *p1Destination)
            pb.p1 = (*p1Y / 16.f + *uiStep / 64.f);
        else if(*p1Y > *p1Destination)
            pb.p1 = (*p1Y / 16.f - *uiStep / 64.f);
        else if(*p1Y = *p1Destination)
            pb.p1 = (*p1Y / 16.f);

        if(*p2Y < *p2Destination)
            pb.p2 = (*p2Y / 16.f + *uiStep / 64.f);
        else if(*p2Y > *p2Destination)
            pb.p2 = (*p2Y / 16.f - *uiStep / 64.f);
        else if(*p2Y = *p2Destination)
            pb.p2 = (*p2Y / 16.f);

        if(*bossY < *bossDestination)
            pb.boss = (*bossY / 16.f + *uiStep / 64.f);
        else if(*bossY > *bossDestination)
            pb.boss = (*bossY / 16.f - *uiStep / 64.f);
        else if(*bossY = *bossDestination)
            pb.boss = (*bossY / 16.f);

        pb.p1State = true;
        pb.p2State = true;
        pb.bossHP = health->value();

        /*memcpy(pb.p1Bullets, bulletsX, sizeof(int) * 5);
        memcpy(pb.p2Bullets, bulletsX + 5, sizeof(int) * 5);
        memcpy(pb.bossL, bulletsX + 10, sizeof(int) * 5);
        memcpy(pb.bossR, bulletsX + 15, sizeof(int) * 5);

        memcpy(pb.p1Y, bulletsY, sizeof(int) * 5);
        memcpy(pb.p2Y, bulletsY + 5, sizeof(int) * 5);
        memcpy(pb.bossLY, bulletsY + 10, sizeof(int) * 5);
        memcpy(pb.bossRY, bulletsY + 15, sizeof(int) * 5);
        *///qDebug() << "pb[" << pb.p1 << "][" << pb.p2 << "][" << pb.boss << "]";
        ui1Update(pb);
        ui2Update(pb);
    });

    scoreboard = new QFrame();
    container->addWidget(scoreboard);
    QHBoxLayout *layout = new QHBoxLayout(scoreboard);
    container->addLayout(layout);
    QLabel *p1Image = new QLabel();
    QLabel *p1Name = new QLabel("P1");
    QLabel *p1BulletCount = new QLabel("5x");
    QLabel *p1Bullet = new QLabel();
    health = new QProgressBar();
    QLabel *p2Image = new QLabel();
    QLabel *p2Name = new QLabel("P2");
    QLabel *p2BulletCount = new QLabel("5x");
    QLabel *p2Bullet = new QLabel();
    p1Image->setStyleSheet("image: url(:/images/pingboss/p1.png);");
    p2Image->setStyleSheet("image: url(:/images/pingboss/p2.png);");
    p1Bullet->setStyleSheet("image: url(:/images/pingboss/playershot1.png)");
    p2Bullet->setStyleSheet("image: url(:/images/pingboss/playershot2.png)");
    p1Bullet->setMinimumHeight(40);
    p2Bullet->setMinimumHeight(40);
    p1Bullet->setMinimumWidth(40);
    p2Bullet->setMinimumWidth(40);
    p1Image->setMinimumHeight(40);
    p1Image->setMinimumWidth(40);
    p2Image->setMinimumHeight(40);
    p2Image->setMinimumWidth(40);
    p1Name->setStyleSheet("font: bold 14pt Ubuntu;");
    p2Name->setStyleSheet("font: bold 14pt Ubuntu;");
    health->setMinimum(0);
    health->setMaximum(6);
    health->setValue(6);
    health->setFormat("Boss HP");
    layout->addWidget(p1Name);
    layout->addWidget(p1Image);
    layout->addWidget(p1BulletCount);
    layout->addWidget(p1Bullet);
    layout->addSpacerItem(new QSpacerItem(1,1,QSizePolicy::Expanding));
    layout->addWidget(health);
    layout->addSpacerItem(new QSpacerItem(1,1,QSizePolicy::Expanding));
    layout->addWidget(p2Bullet);
    layout->addWidget(p2BulletCount);
    layout->addWidget(p2Image);
    layout->addWidget(p2Name);
    scoreboard->setVisible(false);
}

void PingBossLogic::resetVariables()
{
    *bossDestination = rand()%16;
    *p1Destination = 8;
    *p2Destination = 8;
    *p1Y = 8;
    *p2Y = 8;
    *bossY = 8;
    *uiStep = 0;
    health->setValue(6);
    memset(bulletsX, -99, sizeof(int) * 20);
    memset(bulletsY, -1, sizeof(int) * 20);
}

void PingBossLogic::resetALL()
{

}

void PingBossLogic::showScoreboard()
{
    scoreboard->setVisible(true);
}

void PingBossLogic::packetReceived(packet p, int i)
{
    /*
    struct {
        uint8_t p1pos;
        uint8_t p2pos;
        uint8_t bossPos;
        uint8_t bossHp;
        uint8_t pressedButton;

        //Shots elemanlarinin ilk 4 biti x koordinati sonraki 4 biti y koordinati
        uint8_t bossBullets[10];  //x koordinati 0 ise dizi elemani bos/atis yok
        uint8_t p1Bullets[5];   //x koordinati 0 ise dizi elemani bos/atis yok
        uint8_t p2Bullets[5];    //x koordinati 0 ise dizi elemani bos/atis yok
      } ping_boss;
    */

    switch (p.data.ping_boss.pressedButton) {
    case 0:
        if(i == 1)
            *p1Destination = *p1Destination - 1;
        else if (i == 2)
            *p2Destination = *p2Destination - 1;
        break;
        qDebug() << "yukari" << *p1Destination << *p2Destination;
    case 1:
        if(i == 1)
            *p1Destination = *p1Destination + 1;
        else if (i == 2)
            *p2Destination = *p2Destination + 1;
        break;
        qDebug() << "asagi" << *p1Destination << *p2Destination;
    case 2:
        switch (i) {
        case 1:
            // send player 1 bullet
            for(int i = 0 ; i < 5 ; ++i){
                if(bulletsY[i] == -1){
                    bulletsY[i] = *p1Y;
                    bulletsX[i] = 3;
                    break;
                }
            }
            break;
        case 2:
            // send player 2 bullet
            for(int i = 0, j = 5 ; i < 5 ; ++i){
                if(bulletsY[i + j] == -1){
                    bulletsY[i + j] = *p2Y;
                    bulletsX[i + j] = 3;
                    break;
                }
            }
            break;
        default:
            break;
        }
        break;
    default:
        qDebug() << "WHAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAT";
        break;
    }

    if(*p1Destination < 3)
        *p1Destination = 3;
    else if(*p1Destination > 13)
        *p1Destination = 13;

    if(*p2Destination < 3)
        *p2Destination = 3;
    else if(*p2Destination > 13)
        *p2Destination = 13;

    if(!uiUpdater->isActive())
        uiUpdater->start(500);
    if(!stepper->isActive())
        stepper->start(2000);

    /*if(p.data.ping_boss.pressedButton == 2){
        if(i == 1){
            p.data.
        }
    }*/
}
