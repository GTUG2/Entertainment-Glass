#include "xoxlogic.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>

XOXLogic::XOXLogic(QObject *parent, QHBoxLayout *container) : QObject(parent)
{

    turn = 1;
    scorep1 = 0;
    scorep2 = 0;
    roundWinner = 0;
    gameWinner = 0;
    emptyCell = 9;
    haveWinner = 0;
    currentRound = 0;
    memset(board, 0, sizeof(board));

    scoreboard = new QFrame();
    container->addWidget(scoreboard);
    QHBoxLayout *layout = new QHBoxLayout(scoreboard);
    container->addLayout(layout);
    QLabel *p1Image = new QLabel();
    QLabel *p1Name = new QLabel("P1");
    scores = new QLabel("0:0");
    QLabel *p2Image = new QLabel();
    QLabel *p2Name = new QLabel("P2");
    p1Image->setStyleSheet("image: url(:/images/xox/x_piece.png);");
    p2Image->setStyleSheet("image: url(:/images/xox/o_piece.png);");
    p1Image->setMinimumHeight(40);
    p1Image->setMinimumWidth(40);
    p2Image->setMinimumHeight(40);
    p2Image->setMinimumWidth(40);
    p1Name->setStyleSheet("font: bold 14pt Ubuntu;");
    p2Name->setStyleSheet("font: bold 14pt Ubuntu;");
    scores->setStyleSheet("font: bold 14pt Ubuntu;");
    layout->addWidget(p1Name);
    layout->addWidget(p1Image);
    layout->addSpacerItem(new QSpacerItem(1,1,QSizePolicy::Expanding));
    layout->addWidget(scores);
    layout->addSpacerItem(new QSpacerItem(1,1,QSizePolicy::Expanding));
    layout->addWidget(p2Name);
    layout->addWidget(p2Image);
    scoreboard->setVisible(false);
}
void XOXLogic::resetALL(){
    turn = 1;
    scorep1 = 0;
    scorep2 = 0;
    roundWinner = 0;
    gameWinner = 0;
    emptyCell = 9;
    haveWinner = 0;
    currentRound = 0;
    memset(board, 0, sizeof(board));
}

void XOXLogic::showScoreboard()
{
    scoreboard->setVisible(true);
}

void XOXLogic::resetVariables(){
    turn = 1;
    roundWinner = 0;
    emptyCell = 9;
    haveWinner = 0;
    memset(board,0, sizeof(board));
}

void XOXLogic::packetReceived(packet p, int i)
{
    xox p1 = {10,0,10,0,{10,10,10},0},p2 = {10,0,10,0,{10,10,10},0};
    /*
    int cursor;
    int stamp;
    int position;
    int f;
    int winner[3];
    int reset;*/
    p1.cursor = i == 1 ? p.data.xox.position : 10;
    p2.cursor = i == 2 ? p.data.xox.position : 10;
    p1.f = p2.f = false;
    if(p.app_id == 99){
        blSendData(p);
        changeUIRequest(0);
        scoreboard->setVisible(false);
        resetALL();
        uiReset();
        return;
    }
    uint8_t p2_app_id=1;
    packet p_to_send;
    memset(&p_to_send,0,sizeof(p_to_send));

    // implement game logic here
    if(board[p.data.xox.position] == 0 && p.data.xox.isClicked ){
        p1.stamp = p2.stamp = turn;
        p1.position = p2.position = p.data.xox.position;
        board[p.data.xox.position] = turn;
        if(((board[0] == board[1]) && (board[0] != 0) && (board[1] == board[2]) && (board[1] != 0))||
           ((board[0] == board[3]) && (board[0] != 0) && (board[3] == board[6]) && (board[3] != 0)) ||
           ((board[5] == board[8]) && (board[5] != 0) && (board[2] == board[5]) && (board[2] != 0)) ||
           ((board[6] == board[7]) && (board[6] != 0) && (board[7] == board[8]) && (board[7] != 0)) ||
           ((board[2] == board[4]) && (board[2] != 0) && (board[4] == board[6]) && (board[4] != 0)) ||
           ((board[0] == board[4]) && (board[0] != 0) && (board[4] == board[8]) && (board[4] != 0)) ||
           ((board[3] == board[4]) && (board[3] != 0) && (board[4] == board[5]) && (board[4] != 0)) ||
           ((board[1] == board[4]) && (board[1] != 0) && (board[4] == board[7]) && (board[4] != 0))
           ){
            if((board[0] == board[1])&& (board[0] != 0) && (board[1] == board[2])){
                board[0]  +=2;
                board[1]  +=2;
                board[2]  +=2;
                p1.f = p2.f = true;
                p1.winner[0] = p2.winner[0] = 0;
                p1.winner[1] = p2.winner[1] = 1;
                p1.winner[2] = p2.winner[2] = 2;
            }
            else if((board[0] == board[3]) && (board[0] != 0)&& (board[3] == board[6])){
                board[0]  +=2;
                board[3]  +=2;
                board[6]  +=2;
                p1.f = p2.f = true;
                p1.winner[0] = p2.winner[0] = 0;
                p1.winner[1] = p2.winner[1] = 3;
                p1.winner[2] = p2.winner[2] = 6;
            }
            else if((board[2] == board[5])&& (board[2] != 0) && (board[5] == board[8])){
                board[2]  +=2;
                board[5]  +=2;
                board[8]  +=2;
                p1.f = p2.f = true;
                p1.winner[0] = p2.winner[0] = 2;
                p1.winner[1] = p2.winner[1] = 5;
                p1.winner[2] = p2.winner[2] = 8;
            }
            else if((board[6] == board[7])&& (board[6] != 0) && (board[7] == board[8])){
                board[6]  +=2;
                board[7]  +=2;
                board[8]  +=2;
                p1.f = p2.f = true;
                p1.winner[0] = p2.winner[0] = 6;
                p1.winner[1] = p2.winner[1] = 7;
                p1.winner[2] = p2.winner[2] = 8;
            }
            else if((board[2] == board[4]) && (board[2] != 0)&& (board[4] == board[6])){
                board[2]  +=2;
                board[4]  +=2;
                board[6]  +=2;
                p1.f = p2.f = true;
                p1.winner[0] = p2.winner[0] = 2;
                p1.winner[1] = p2.winner[1] = 4;
                p1.winner[2] = p2.winner[2] = 6;
            }
            else if((board[0] == board[4])&& (board[0] != 0) && (board[4] == board[8])){
                board[0]  +=2;
                board[4]  +=2;
                board[8]  +=2;
                p1.f = p2.f = true;
                p1.winner[0] = p2.winner[0] = 0;
                p1.winner[1] = p2.winner[1] = 4;
                p1.winner[2] = p2.winner[2] = 8;
            }else if((board[3] == board[4])&& (board[3] != 0) && (board[4] == board[5])){
                board[3]  +=2;
                board[4]  +=2;
                board[5]  +=2;
                p1.f = p2.f = true;
                p1.winner[0] = p2.winner[0] = 3;
                p1.winner[1] = p2.winner[1] = 4;
                p1.winner[2] = p2.winner[2] = 5;
            }else if((board[1] == board[4])&& (board[1] != 0) && (board[4] == board[7])){
                board[1]  +=2;
                board[4]  +=2;
                board[7]  +=2;
                p1.f = p2.f = true;
                p1.winner[0] = p2.winner[0] = 1;
                p1.winner[1] = p2.winner[1] = 4;
                p1.winner[2] = p2.winner[2] = 7;
            }
            currentRound++;
            if(turn == 1){
                haveWinner = 1;
                roundWinner = 1;
                ++scorep1;
            }
            else if(turn == 2){
                haveWinner = 1;
                roundWinner = 2;
                ++scorep2;
            }
        }
        emptyCell--;

        turn = p_to_send.data.xox.turn = 3 - turn;
    }else{
        p_to_send.data.xox.turn = turn;
    }
    if(emptyCell == 0 ){
        currentRound++;
    }

    // GAME OVER!
    if(currentRound == MAX_ROUND){
        if(scorep1 > scorep2){
            gameWinner = 1;
        }
        else if(scorep2 > scorep1){
            gameWinner = 2;
        }
        else{
            gameWinner = 3;
        }

    }


    if(emptyCell == 0 && haveWinner == 0){
        roundWinner = 3;
    }

    if(p.data.xox.isClicked){
        p_to_send.start = 127;
        p_to_send.app_id = XOX_ID;
        p_to_send.data.xox.scorep1 = scorep1;
        p_to_send.data.xox.scorep2 = scorep2;
        p_to_send.data.xox.turn = turn;
        p_to_send.data.xox.winGame = gameWinner;
        p_to_send.data.xox.winRound = roundWinner;
        for (int i = 0; i < 9; ++i) {
            p_to_send.data.xox.cell_states[i] = board[i];
        }
        bl1SendData(p_to_send);
        bl2SendData(p_to_send);

        if(gameWinner != 0){
            packet p3;
            memcpy(&p3,&p_to_send,sizeof(p3));
            p3.app_id = 0;
            QTimer *timerlel2 = new QTimer(this);
            timerlel2->setSingleShot(true);
            connect(timerlel2, &QTimer::timeout, [=]() {
                emit changeUIRequest(0);
                scoreboard->setVisible(false);
                bl1SendData(p3);
                bl2SendData(p3);
                timerlel2->deleteLater();
                resetALL();
                uiReset();
            } );
            timerlel2->start(4000);

            switch (gameWinner) {
            case 1:
                p_to_send.app_id = 9;
                p2_app_id = 10;
                emit p1Message(9, "Tebrikler kazandın!!!");
                emit p2Message(10, "Bir dahaki sefere");
                emit changeUIRequest(9);
                scoreboard->setVisible(false);
                break;
            case 2:
                p_to_send.app_id = 10;
                p2_app_id = 9;
                emit p2Message(9, "Tebrikler kazandın!!!");
                emit p1Message(10, "Bir dahaki sefere");
                emit changeUIRequest(10);
                scoreboard->setVisible(false);
                break;
            case 3:
                p_to_send.app_id = 11;
                p2_app_id = 11;
                emit p1Message(11, "Berabere");
                emit p2Message(11, "Berabere");
                emit changeUIRequest(11);
                scoreboard->setVisible(false);
                break;
            default:
                break;
            }

            packet p2;
            memcpy(&p2,&p_to_send,sizeof(p2));
            p2.app_id = p2_app_id;
            QTimer *timerlel = new QTimer(this);
            timerlel->setSingleShot(true);
            connect(timerlel, &QTimer::timeout, [=]() {
                bl1SendData(p_to_send);
                bl2SendData(p2);
                timerlel->deleteLater();
            } );
            timerlel->start(2000);
            resetALL();
        }
    }



    if(roundWinner != 0 && gameWinner != 1){
        resetVariables();
        p_to_send.start = 127;
        p_to_send.app_id = XOX_ID;
        p_to_send.data.xox.scorep1 = scorep1;
        p_to_send.data.xox.scorep2 = scorep2;
        p_to_send.data.xox.turn = turn;
        p_to_send.data.xox.winGame = gameWinner;
        p_to_send.data.xox.winRound = roundWinner;
        for (int i = 0; i < 9; ++i) {
            p_to_send.data.xox.cell_states[i] = board[i];
        }
        QTimer *timer = new QTimer(this);
        timer->setSingleShot(true);
        connect(timer, &QTimer::timeout, [=]() {
            bl1SendData(p_to_send);
            bl2SendData(p_to_send);
            timer->deleteLater();
            emit uiReset();
        } );
        timer->start(2000);
    }


    emit ui1Update(p1);
    emit ui2Update(p2);
    scores->setText(QString::number(scorep1) + ":" + QString::number(scorep2));
}
