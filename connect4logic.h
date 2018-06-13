class connect4frame;

#ifndef CONNECT4LOGIC_H
#define CONNECT4LOGIC_H

#include <QObject>
#include "common.h"
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QTimer>

#define MAX_ROUND 5

class connect4logic : public QObject
{
    Q_OBJECT
public:
    explicit connect4logic(QObject *parent = nullptr, QHBoxLayout *container = nullptr);
    int board[6][7]; // 1 = X , 2 = O
    connect4frame *c4ui;
    int getEmptyCell();
    int getHaveWinner();
    int cursor=0;
    int roundWinner; // 0 = NOTHING , 1 = PLAYER1 , 2= PLAYER2, 3=DRAW
    int frame_x1,frame_y1, frame_x2,frame_y2, frame_x3,frame_y3, frame_x4,frame_y4;
    int x1_loc, y1_loc, x2_loc, y2_loc;
    void showScoreboard();
signals:
    void ui1Update();
    void ui2Update();
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
    //int roundWinner; // 0 = NOTHING , 1 = PLAYER1 , 2= PLAYER2, 3=DRAW
    int turn;
    int emptyCell;
    int haveWinner;

    QFrame *scoreboard;
    QLabel *scores;

    void resetALL();
    void resetVariables();
    void fillp1p2(int board[6][7], uint8_t p1[6], uint8_t p2[7]);
    int winCheck(uint8_t row1, uint8_t col1,uint8_t &x1,uint8_t &y1,uint8_t &x2,uint8_t &y2);

};

#endif // CONNECT4LOGIC_H
