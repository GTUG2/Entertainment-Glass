#include "connect4logic.h"
#include <QDebug>

connect4logic::connect4logic(QObject *parent, QHBoxLayout *container) : QObject(parent)
{
    turn = 1;
    scorep1 = 0;
    scorep2 = 0;
    roundWinner = 0;
    gameWinner = 0;
    emptyCell = 6 * 7;
    haveWinner = 0;
    currentRound = 0;
    memset(board, 0, sizeof(board));
    x1_loc = 0;
    y1_loc = 0;
    x2_loc = 0;
    y2_loc = 0;
    frame_x1 = 0;
    frame_y1 = 0;
    frame_x2 = 0;
    frame_y2 = 0;
    frame_x3 = 0;
    frame_y3 = 0;
    frame_x4=0 ;
    frame_y4 = 0;
    scoreboard = new QFrame();
    container->addWidget(scoreboard);
    QHBoxLayout *layout = new QHBoxLayout(scoreboard);
    container->addLayout(layout);
    QLabel *p1Image = new QLabel();
    QLabel *p1Name = new QLabel("P1");
    scores = new QLabel("0:0");
    QLabel *p2Image = new QLabel();
    QLabel *p2Name = new QLabel("P2");
    p1Image->setStyleSheet("image: url(:/images/c4/p1_piece.png);");
    p2Image->setStyleSheet("image: url(:/images/c4/p2_piece.png);");
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
void connect4logic::resetALL(){
    turn = 1;
    scorep1 = 0;
    scorep2 = 0;
    roundWinner = 0;
    gameWinner = 0;
    emptyCell = 6 * 7;;
    haveWinner = 0;
    currentRound = 0;
    memset(board, 0, sizeof(board));
}

void connect4logic::resetVariables(){
    turn = 1;
    roundWinner = 0;
    emptyCell = 6 * 7;
    haveWinner = 0;
    memset(board,0, sizeof(board));
}

int connect4logic::getEmptyCell(){
    return emptyCell;
}
int connect4logic::getHaveWinner(){
    return haveWinner;
}

void connect4logic::showScoreboard()
{
    scoreboard->setVisible(true);
}

void connect4logic::packetReceived(packet p, int i)
{
    uint8_t x1=0,y1=0,x2=0,y2=0;
    int roundWon = 0;
    cursor = p.data.connect_four.position;
    if(p.app_id == 99){
        resetALL();
        blSendData(p);
        changeUIRequest(0);
        scoreboard->setVisible(false);
        return;
    }

    uint8_t p2_app_id=2;
    packet p_to_send;
    memset(&p_to_send,0,sizeof(p_to_send));

    if(p.data.connect_four.is_clicked){
        for(uint8_t i=5; i>=0; --i){
            if(board[i][p.data.connect_four.position] == 0){
                board[i][p.data.connect_four.position] = turn;

                emptyCell--;
                if(winCheck(i,p.data.connect_four.position,x1,y1,x2,y2)){
                    roundWon = 1;
                    currentRound++;
                    x1_loc = x1;
                    y1_loc = y1;
                    x2_loc = x2;
                    y2_loc = y2;

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
                emit ui1Update();
                emit ui2Update();
                turn = 3 - turn;
                if(emptyCell==0){
                    currentRound++;
                }

                if(emptyCell == 0 && haveWinner == 0){
                    roundWinner = 3;
                }

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

                p_to_send.start = 127;
                p_to_send.app_id = CONNECT4_ID;
                p_to_send.data.connect_four.scoreP1 = scorep1;
                p_to_send.data.connect_four.scoreP2 = scorep2;
                p_to_send.data.connect_four.turn = turn;
                fillp1p2(board,p_to_send.data.connect_four.p1_cells,p_to_send.data.connect_four.p2_cells);
                p_to_send.data.connect_four.roundWon = roundWon;
                p_to_send.data.connect_four.x1 = x1;
                p_to_send.data.connect_four.y1 = y1;
                p_to_send.data.connect_four.x2 = x2;
                p_to_send.data.connect_four.y2 = y2;

                blSendData(p_to_send);

                if(gameWinner != 0){
                    packet p3;
                    packet p4;
                    memcpy(&p3,&p_to_send,sizeof(p3));
                    memcpy(&p4,&p_to_send,sizeof(p4));
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
                    } );
                    timerlel2->start(4000);

                    switch (gameWinner) {
                    case 1:
                        p4.app_id = 9;
                        p2_app_id = 10;
                        emit p1Message(9, "Tebrikler kazandın!!!");
                        emit p2Message(10, "Bir dahaki sefere");
                        emit changeUIRequest(9);
                        scoreboard->setVisible(false);
                        break;
                    case 2:
                        p4.app_id = 10;
                        p2_app_id = 9;
                        emit p2Message(9, "Tebrikler kazandın!!!");
                        emit p1Message(10, "Bir dahaki sefere");
                        emit changeUIRequest(10);
                        scoreboard->setVisible(false);
                        break;
                    case 3:
                        p4.app_id = 11;
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
                        bl1SendData(p4);
                        bl2SendData(p2);
                        timerlel->deleteLater();
                    } );
                    timerlel->start(2000);
                    resetALL();
                }

                if(roundWinner != 0 && gameWinner == 0){
                    packet p2lelo;
                    memset(&p2lelo,0,sizeof(p2lelo));
                    p2lelo.start = 127;
                    p2lelo.app_id = CONNECT4_ID;
                    p2lelo.data.connect_four.scoreP1 = scorep1;
                    p2lelo.data.connect_four.scoreP2 = scorep2;
                    p2lelo.data.connect_four.turn = 1;
                    p2lelo.data.connect_four.roundWon = 0;

                    QTimer *timer = new QTimer(this);
                    timer->setSingleShot(true);
                    connect(timer, &QTimer::timeout, [=]() {
                        bl1SendData(p2lelo);
                        bl2SendData(p2lelo);
                        emit ui1Update();
                        emit ui2Update();
                        timer->deleteLater();
                    } );
                    timer->start(2000);
                    emit ui1Update();
                    emit ui2Update();
                    resetVariables();
                  if(roundWon == 1){
                        emit p1Message(9, "Roundu 1 Player 1 Kazandı!!!");
                    }
                    else if(roundWon == 2){
                        emit p2Message(9, "Roundu 1 Player 2 Kazandı!!!");
                    }

                }

                break;
            }
        }
    }else{
        emit ui1Update();
        emit ui2Update();
    }
    scores->setText(QString::number(scorep1) + ":" + QString::number(scorep2));

    /*for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            qDebug() << board[i][j] << " ";
        }
        qDebug() << "\n";
    }*/
    /*packet pkt;
    memset(&pkt, 0, sizeof(p));
    pkt.start=127;
    pkt.app_id = 2;
    pkt.data.connect_four.turn = turn  = 3-turn;
    pkt.data.connect_four.p1_cells[5] = 0b00001111;
    pkt.data.connect_four.p2_cells[5] = 0b11110000;
    pkt.data.connect_four.p2_cells[4] = 0b11110000;




    emit blSendData(pkt);*/

}

void connect4logic::fillp1p2(int board[6][7], uint8_t p1[6], uint8_t p2[7]){
    int bit_masks[8]= {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
    qDebug()<<"before";
    for (int i = 0; i < 6; ++i) {
        qDebug()<<p1[i];
    }
    for (int i = 0; i < 6; ++i) {
        qDebug()<<p2[i];
    }
    for(int i=0; i<6; ++i){
        for (int j = 0; j < 7; ++j) {
            if(board[i][j] == 1){
                p1[i] |= bit_masks[j];
            }else if(board[i][j] == 2){
                p2[i] |= bit_masks[j];
            }
        }
    }
    qDebug()<<"after";
    for (int i = 0; i < 6; ++i) {
        qDebug()<<p1[i];
    }
    for (int i = 0; i < 6; ++i) {
        qDebug()<<p2[i];
    }
}

int connect4logic::winCheck(uint8_t row1, uint8_t col1,uint8_t &x1,uint8_t &y1,uint8_t &x2,uint8_t &y2){
    int the_way = -1;
    uint8_t counter = 1;
    uint8_t i,j;
    uint8_t break_flag = 0;

    i = row1;
    j = col1;

    x1=col1;
    y1=row1;
    x2=col1;
    y2=row1;

    /*HORIZONTAL CHECK*/
    while(counter < 4){
        break_flag = 0;
        if(the_way == -1 && j == 0){
            break_flag = 1;
            the_way = 1;
            i = row1;
            j = col1;
        }if(the_way == -1 && j > 0){
            break_flag = 1;
            if(board[i][j-1] == board[row1][col1]){
                counter++;
                x1--;
                j--;
            }else if(board[i][j-1] != board[row1][col1]){
                the_way = 1;
                i = row1;
                j = col1;
            }
        }if(the_way == 1 && j < 6){
            break_flag = 1;
            if(board[i][j+1] == board[row1][col1]){
                counter++;
                x2++;
                j++;
            }else{
                break;
            }
        }if(break_flag==0){
            break;
        }
    }
    if(counter == 4){
        return 1;
    }
    /*HORIZONTAL CHECK END*/

    /*VERTICAL CHECK*/
    the_way = -1;
    counter = 1;
    i = row1;
    j = col1;
    x1=col1;
    y1=row1;
    x2=col1;
    y2=row1;
    while(counter < 4){
        break_flag = 0;
        if(the_way == -1 && i > 0){
            break_flag = 1;
            if(board[i-1][j] == board[row1][col1]){
                counter++;
                i--;
                y1--;
            }else{
                the_way = 1;
                i = row1;
                j = col1;
            }
        }if(the_way == -1 && i == 0){
            break_flag = 1;
            the_way = 1;
            i = row1;
            j = col1;
        }
        if(the_way == 1 && i < 5){
            break_flag = 1;
            if(board[i+1][j] == board[row1][col1]){
                counter++;
                i++;
                y2++;
            }else{
                break;
            }
        }if(break_flag==0){
            break;
        }
    }
    if(counter == 4){
        return 1;
    }
    /*VERTICAL CHECK END*/

    /*NW - SE CHECK*/
    the_way = -1;
    counter = 1;
    i = row1;
    j = col1;
    x1=col1;
    y1=row1;
    x2=col1;
    y2=row1;
    while(counter < 4){
        break_flag = 0;
        if(the_way == -1 && i > 0 && j > 0){
            break_flag = 1;
            if(board[i-1][j-1] == board[row1][col1]){
                counter++;
                i--;
                j--;
                x1--;
                y1--;
            }else{
                the_way = 1;
                i = row1;
                j = col1;
            }
        }if(the_way == -1 && (i == 0 || j == 0)){
            break_flag = 1;
            the_way = 1;
            i = row1;
            j = col1;
        }if(the_way == 1 && i < 5 && j < 6){
            break_flag = 1;
            if(board[i+1][j+1] == board[row1][col1]){
                counter++;
                i++;
                j++;
                x2++;
                y2++;
            }else{
                break;
            }
        }if(break_flag == 0){
            break;
        }
    }
    if(counter == 4){
        return 1;
    }
    /*NW - SE CHECK END*/


    /*NE - SW CHECK*/
    the_way = -1;
    counter = 1;
    i = row1;
    j = col1;
    x1=col1;
    y1=row1;
    x2=col1;
    y2=row1;
    while(counter < 4){
        break_flag= 0;
        if(the_way == -1 && i > 0 && j < 6){
            break_flag = 1;
            if(board[i-1][j+1] == board[row1][col1]){
                counter++;
                i--;
                j++;
                y1--;
                x1++;
            }else{
                the_way = 1;
                i = row1;
                j = col1;
            }
        }if(the_way == -1 && (i == 0 || j == 6)){
            break_flag = 1;
            the_way = 1;
            i = row1;
            j = col1;
        }if(the_way == 1 && i < 5 && j > 0){
            break_flag = 1;
            if(board[i+1][j-1] == board[row1][col1]){
                counter++;
                i++;
                j--;
                y2++;
                x2--;
            }else{
                break;
            }
        }
        if(break_flag == 0){
            break;
        }
    }
    if(counter == 4){
        return 1;
    }else{
        return 0;
    }
    /*NE - SW CHECK END*/
}
