#ifndef PINGBOSSLOGIC_H
#define PINGBOSSLOGIC_H

#include "common.h"

#include <QObject>
#include <QHBoxLayout>
#include <QFrame>
#include <QProgressBar>
#include <QTimer>

class PingBossLogic : public QObject
{
    Q_OBJECT
public:
    explicit PingBossLogic(QObject *parent = nullptr, QHBoxLayout *container = nullptr);
    void resetVariables();
    void resetALL();
    void showScoreboard();

signals:
    void ui1Update(pingboss);
    void ui2Update(pingboss);
    void uiReset();
    void bl1SendData(packet);
    void bl2SendData(packet);
    void blSendData(packet);
    void changeUIRequest(int);
    void p1Message(int, QString);
    void p2Message(int, QString);

public slots:
    void packetReceived(packet, int);

private:
    QFrame *scoreboard;
    QProgressBar *health;

    int *uiStep;
    int *bossDestination;
    int *p1Destination;
    int *p2Destination;

    int *bossY;
    int *p1Y;
    int *p2Y;

    int bulletsX[20]; // 0-5 is player 1, 5-10 is player 2, 10-15 boss left, 15-20 boss right
    int bulletsY[20]; // 0-5 is player 1, 5-10 is player 2, 10-15 boss left, 15-20 boss right

    QTimer *stepper; // updates the logical state
    QTimer *uiUpdater; // updates the ui for interpolation
};

#endif // PINGBOSSLOGIC_H
