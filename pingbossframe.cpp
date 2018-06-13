#include "pingbossframe.h"
#include "ui_pingbossframe.h"

#include <QDebug>
#include <QPushButton>

#define BOSS_X 173
#define BOSS_Y 295
#define P1_X 0
#define P2_X 394
#define P1_Y 344
#define P2_Y 344

#define PB(IMG_NAME) "image: url(:/images/pingboss/"+QString(IMG_NAME)+")"

#define BOSS PB("boss.png")
#define BOSS_DEAD PB("bossdead.png")
#define BOSS_SHOT1 PB("bossshot1.png")
#define BOSS_SHOT2 PB("bossshot1.png")
#define P1 PB("p1.png")
#define P1_DEAD PB("p1dead.png")
#define P2 PB("p2.png")
#define P2_DEAD PB("p2dead.png")
#define PLAYER_SHOT1 PB("playershot1.png")
#define PLAYER_SHOT2 PB("playershot2.png")

#define P1_BULLET(POSX) 50 + 200 * POSX
#define P2_BULLET(POSX) 400 - 200 * POSX
#define BOSS_BULLET_L(POSX) 200 - 200 * POSX
#define BOSS_BULLET_R(POSX) 250 + 200 * POSX

PingBossFrame::PingBossFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::PingBossFrame)
{
    ui->setupUi(this);
    for(int i = 0 ; i < 5 ; ++i){
        QLabel *bullet = new QLabel(this);
        bullet->setGeometry(-100, -100, 25, 50);
        bullet->setStyleSheet(PLAYER_SHOT1);
        bullets[i] = bullet;
    }

    for(int i = 5 ; i < 10 ; ++i){
        QLabel *bullet = new QLabel(this);
        bullet->setGeometry(-100, -100, 25, 50);
        bullet->setStyleSheet(PLAYER_SHOT2);
        bullets[i] = bullet;
    }

    for(int i = 10 ; i < 20 ; ++i){
        QLabel *bullet = new QLabel(this);
        bullet->setGeometry(-100, -100, 25, 50);
        bullet->setStyleSheet(BOSS_SHOT1);
        bullets[i] = bullet;
    }
}

PingBossFrame::~PingBossFrame()
{
    delete ui;
}

void PingBossFrame::updateUI(pingboss p)
{
    /*
    struct pingboss{
        float p1;
        float p2;
        float boss;
        float p1Bullets[5];
        int p1Y[5];
        float p2Bullets[5];
        int p2Y[5];
        float bossL[5];
        int bossLY[5];
        float bossR[5];
        int bossRY[5];
        bool p1State;
        bool p2State;
        bool bossState;
    };
    */

    ui->p1->move(P1_X, P1_Y * p.p1);
    ui->p2->move(P2_X, P2_Y * p.p2);
    ui->boss->move(BOSS_X, BOSS_Y * p.boss);
    if(!p.p1State)
        ui->p1->setStyleSheet(P1_DEAD);
    if(!p.p2State)
        ui->p2->setStyleSheet(P2_DEAD);
    if(p.bossHP == 0)
        ui->boss->setStyleSheet(BOSS_DEAD);

    for(int i = 0 ; i < 5 ; ++i){
        if(p.p1Y[i] == -1)
            bullets[i]->move(-100, -100);
        else{
            qDebug() << "P1_BULLET" << P1_BULLET(p.p1Bullets[i]) << "," << p.p2Y[i] * 25 << ")";
            bullets[i]->move(P1_BULLET(p.p1Bullets[i]), p.p1Y[i] * 25);
            //qDebug() << "P1[" << i << "] =" << P1_BULLET(p.p1Bullets[i]) << " | " << p.p1Y[i] * 25;
        }
    }

    for(int i = 0, j = 5; i < 5 ; ++i){
        if(p.p2Y[i] == -1)
            bullets[i + j]->move(-100, -100);
        else{
            qDebug() << "P2_BULLET(" << P2_BULLET(p.p2Bullets[i]) << "," << p.p2Y[i] * 25 << ")";
            bullets[i + j]->move(P2_BULLET(p.p2Bullets[i]), p.p2Y[i] * 25);
            //qDebug() << "P2[" << i << "] =" << P2_BULLET(p.p2Bullets[i]) << " | " << p.p2Y[i] * 25;
        }
    }

    for(int i = 0, j = 10 ; i < 5 ; ++i){
        if(p.bossLY[i] == -1)
            bullets[i + j]->move(-100, -100);
        else{
            bullets[i + j]->move(BOSS_BULLET_L(p.bossL[i]), p.bossLY[i] * 25);
            //qDebug() << "BL[" << i << "] =" << P2_BULLET(p.bossL[i]) << " | " << p.bossLY[i] * 25;
        }
    }

    for(int i = 0, j = 15 ; i < 5 ; ++i){
        if(p.bossRY[i] == -1)
            bullets[i + j]->move(-100, -100);
        else{
            bullets[i + j]->move(BOSS_BULLET_R(p.bossR[i]), p.bossRY[i] * 25);
            //qDebug() << "BR[" << i << "] =" << P2_BULLET(p.bossR[i]) << " | " << p.bossRY[i] * 25;
        }
    }
}

void PingBossFrame::resetUI()
{
    ui->p1->setStyleSheet(P1);
    ui->p2->setStyleSheet(P2);
    ui->p1->move(P1_X, 172);
    ui->p2->move(P2_X, 172);
    ui->p2->move(173, 295 * 1 / (float)(rand()%294 + 1));
    ui->boss->setStyleSheet(BOSS);
}
