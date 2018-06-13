class XOXFrame;
#ifndef XOXLOGIC_H
#define XOXLOGIC_H
#define MAX_ROUND 3
#include "common.h"
#include <QObject>
#include <QTimer>
#include <QApplication>
#include <QHBoxLayout>
#include <QFrame>
#include <QLabel>

class XOXLogic : public QObject
{
    Q_OBJECT
public:
    explicit XOXLogic(QObject *parent = nullptr, QHBoxLayout *container = nullptr);
    void resetVariables();
    void resetALL();
    void showScoreboard();

signals:
    void ui1Update(xox);
    void ui2Update(xox);
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
    int scorep1;
    int scorep2;
    int currentRound;
    int gameWinner; // 0 = NOTHING , 1 = PLAYER1 , 2= PLAYER2, 3=DRAW
    int roundWinner; // 0 = NOTHING , 1 = PLAYER1 , 2= PLAYER2, 3=DRAW
    int turn;
    int board[9];
    int emptyCell;
    int haveWinner;
    QFrame *scoreboard;
    QLabel *scores;
};

#endif // XOXLOGIC_H
