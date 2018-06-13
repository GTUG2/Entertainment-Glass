#include "connect4frame.h"
#include "ui_connect4frame.h"
#include <QDebug>

QString* styleSheets_empty = new QString[18] {
    QString("image: url(://images/c4/empty.svg);"), // normal empty
    QString("image: url(://images/c4/empty_cursor.svg);"), // cursor empty
    QString("image: url(://images/c4/empty_ll.svg);"), // normal p1
    QString("image: url(://images/c4/empty_lr.png);"), // normal p1
    QString("image: url(://images/c4/empty_ul.svg);"), // normal p1
    QString("image: url(://images/c4/empty_ur.png);"), // normal p1
    QString("image: url(://images/c4/empty_win_column.svg);"), // normal empty
    QString("image: url(://images/c4/empty_win_e.svg);"), // normal empty
    QString("image: url(://images/c4/empty_win_lcross.svg);"), // normal empty
    QString("image: url(://images/c4/empty_win_n.svg);"), // normal empty
    QString("image: url(://images/c4/empty_win_ne.svg);"), // normal empty
    QString("image: url(://images/c4/empty_win_nw.svg);"), // normal empty
    QString("image: url(://images/c4/empty_win_rcross.svg);"), // normal empty
    QString("image: url(://images/c4/empty_win_row.svg);"), // normal empty
    QString("image: url(://images/c4/empty_win_s.svg);"), // normal empty
    QString("image: url(://images/c4/empty_win_se.svg);"), // normal empty
    QString("image: url(://images/c4/empty_win_sw.svg);"), // normal empty
    QString("image: url(://images/c4/empty_win_w.svg);"), // normal empty
};
QString* styleSheets_p1 = new QString[18] {

    QString("image: url(://images/c4/p1.svg);"), // normal p1
    QString("image: url(://images/c4/p1_cursor.svg);"), // normal p1
    QString("image: url(://images/c4/p1_ll.svg);"), // normal p1
    QString("image: url(://images/c4/p1_lr.png);"), // normal p1
    QString("image: url(://images/c4/p1_ul.svg);"), // normal p1
    QString("image: url(://images/c4/p1_ur.png);"), // normal p1
    QString("image: url(://images/c4/p1_win_column.svg);"), // normal p1
    QString("image: url(://images/c4/p1_win_e.svg);"), // normal p1
    QString("image: url(://images/c4/p1_win_lcross.svg);"), // normal p1
    QString("image: url(://images/c4/p1_win_n.svg);"), // normal p1
    QString("image: url(://images/c4/p1_win_ne.svg);"), // normal p1
    QString("image: url(://images/c4/p1_win_nw.svg);"), // normal p1
    QString("image: url(://images/c4/p1_win_rcross.svg);"), // normal p1
    QString("image: url(://images/c4/p1_win_row.svg);"), // normal p1
    QString("image: url(://images/c4/p1_win_s.svg);"), // normal p1
    QString("image: url(://images/c4/p1_win_se.svg);"), // normal p1
    QString("image: url(://images/c4/p1_win_sw.svg);"), // normal p1
    QString("image: url(://images/c4/p1_win_w.svg);"), // normal p1
};
QString* styleSheets_p2 = new QString[18] {

    QString("image: url(://images/c4/p2.svg);"), // normal p2
    QString("image: url(://images/c4/p2_cursor.svg);"), // normal p2
    QString("image: url(://images/c4/p2_ll.svg);"), // normal p2
    QString("image: url(://images/c4/p2_lr.png);"), // normal p2
    QString("image: url(://images/c4/p2_ul.svg);"), // normal p2
    QString("image: url(://images/c4/p2_ur.png);"), // normal p2
    QString("image: url(://images/c4/p2_win_column.svg);"), // normal p2
    QString("image: url(://images/c4/p2_win_e.svg);"), // normal p2
    QString("image: url(://images/c4/p2_win_lcross.svg);"), // normal p2
    QString("image: url(://images/c4/p2_win_n.svg);"), // normal p2
    QString("image: url(://images/c4/p2_win_ne.svg);"), // normal p2
    QString("image: url(://images/c4/p2_win_nw.svg);"), // normal p2
    QString("image: url(://images/c4/p2_win_rcross.svg);"), // normal p2
    QString("image: url(://images/c4/p2_win_row.svg);"), // normal p2
    QString("image: url(://images/c4/p2_win_s.svg);"), // normal p2
    QString("image: url(://images/c4/p2_win_se.svg);"), // normal p2
    QString("image: url(://images/c4/p2_win_sw.svg);"), // normal p2
    QString("image: url(://images/c4/p2_win_w.svg);"), // normal p2

};

connect4frame::connect4frame(connect4logic *c4logic_param, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::connect4frame)
{

    ui->setupUi(this);
    c4logic = c4logic_param;
    for(int i=0; i< BOARD_SIZE;++i){
        lbls[i] = new QLabel();
    }
    lbls[0] = ui->label;
    lbls[1] = ui->label_2;
    lbls[2] = ui->label_3;
    lbls[3] = ui->label_4;
    lbls[4] = ui->label_5;
    lbls[5] = ui->label_6;
    lbls[6] = ui->label_7;
    lbls[7] = ui->label_8;
    lbls[8] = ui->label_9;
    lbls[9] = ui->label_10;
    lbls[10] = ui->label_11;
    lbls[11] = ui->label_12;
    lbls[12] = ui->label_13;
    lbls[13] = ui->label_14;
    lbls[14] = ui->label_15;
    lbls[15] = ui->label_16;
    lbls[16] = ui->label_17;
    lbls[17] = ui->label_18;
    lbls[18] = ui->label_19;
    lbls[19] = ui->label_20;
    lbls[20] = ui->label_21;
    lbls[21] = ui->label_22;
    lbls[22] = ui->label_23;
    lbls[23] = ui->label_24;
    lbls[24] = ui->label_25;
    lbls[25] = ui->label_26;
    lbls[26] = ui->label_27;
    lbls[27] = ui->label_28;
    lbls[28] = ui->label_29;
    lbls[29] = ui->label_30;
    lbls[30] = ui->label_31;
    lbls[31] = ui->label_32;
    lbls[32] = ui->label_33;
    lbls[33] = ui->label_34;
    lbls[34] = ui->label_35;
    lbls[35] = ui->label_36;
    lbls[36] = ui->label_37;
    lbls[37] = ui->label_38;
    lbls[38] = ui->label_39;
    lbls[39] = ui->label_40;
    lbls[40] = ui->label_41;
    lbls[41] = ui->label_42;



    //printBoard();
}
void connect4frame::printBoard(){
    for(int i=0; i<6; ++i){
        for (int j = 0; j < 7; ++j) {
            if(c4logic->board[i][j] == 1)
                if(c4logic->cursor == j)
                    lbls[7*i+j]->setStyleSheet("image: url(://images/c4/p1_cursor.svg);");
                else
                    lbls[7*i+j]->setStyleSheet("image: url(://images/c4/p1.svg);");
            else if(c4logic->board[i][j] == 2)
                if(c4logic->cursor == j)
                    lbls[7*i+j]->setStyleSheet("image: url(://images/c4/p2_cursor.svg);");
                else
                    lbls[7*i+j]->setStyleSheet("image: url(://images/c4/p2.svg);");
            else if(c4logic->cursor == j)
                lbls[7*i+j]->setStyleSheet("image: url(://images/c4/empty_cursor.svg);");
            else
                lbls[7*i+j]->setStyleSheet("image: url(://images/c4/empty.svg);");
        }
    }
    roundWonSet();
    qDebug() << "c4logic->frame_y1*7+c4logic->frame_x1: " <<c4logic->frame_y1*7+c4logic->frame_x1;
    qDebug() << "c4logic->frame_y2*7+c4logic->frame_x2: " <<c4logic->frame_y2*7+c4logic->frame_x2;
    qDebug() << "c4logic->frame_y3*7+c4logic->frame_x3: " <<c4logic->frame_y3*7+c4logic->frame_x3;
    qDebug() << "c4logic->frame_y4*7+c4logic->frame_x4: " <<c4logic->frame_y4*7+c4logic->frame_x4;

    if(c4logic->roundWinner==1){
        lbls[c4logic->frame_y1*7+c4logic->frame_x1]->setStyleSheet(styleSheets_p1[6]);
        lbls[c4logic->frame_y2*7+c4logic->frame_x2]->setStyleSheet(styleSheets_p1[6]);
        lbls[c4logic->frame_y3*7+c4logic->frame_x3]->setStyleSheet(styleSheets_p1[6]);
        lbls[c4logic->frame_y4*7+c4logic->frame_x4]->setStyleSheet(styleSheets_p1[6]);
    }
    if(c4logic->roundWinner==2){
        lbls[c4logic->frame_y1*7+c4logic->frame_x1]->setStyleSheet(styleSheets_p2[6]);
        lbls[c4logic->frame_y2*7+c4logic->frame_x2]->setStyleSheet(styleSheets_p2[6]);
        lbls[c4logic->frame_y3*7+c4logic->frame_x3]->setStyleSheet(styleSheets_p2[6]);
        lbls[c4logic->frame_y4*7+c4logic->frame_x4]->setStyleSheet(styleSheets_p2[6]);
    }

    qDebug() << "Cursor= " << c4logic->cursor;
}
void connect4frame::roundWonSet(){
    //y1==y2
    if(c4logic->y1_loc == c4logic->y2_loc){

        c4logic->frame_y1 = c4logic->y1_loc;
        c4logic->frame_y2 = c4logic->y1_loc;
        c4logic->frame_y3 = c4logic->y1_loc;
        c4logic->frame_y4 = c4logic->y1_loc;

        if(c4logic->x1_loc<c4logic->x2_loc){
            c4logic->frame_x1 = c4logic->x1_loc;
            c4logic->frame_x2 = c4logic->x2_loc;
            c4logic->frame_x3 = c4logic->x1_loc+1;
            c4logic->frame_x4 = c4logic->frame_x3 +1;
        }
        else {
            c4logic->frame_x1 = c4logic->x1_loc;
            c4logic->frame_x2 =c4logic-> x2_loc;
            c4logic->frame_x3 = c4logic->x2_loc+1;
            c4logic->frame_x4 = c4logic->frame_x3 +1;

        }

    }
    //x1==x2
    if(c4logic->x1_loc == c4logic->x2_loc){
        c4logic->frame_x1 = c4logic->x1_loc;
        c4logic->frame_x2 = c4logic->x1_loc;
        c4logic->frame_x3 = c4logic->x1_loc;
        c4logic->frame_x4 = c4logic->x1_loc;

        if(c4logic->y1_loc<c4logic->y2_loc){
            c4logic->frame_y1 = c4logic->y1_loc;
            c4logic->frame_y2 = c4logic->y2_loc;
            c4logic->frame_y3 = c4logic->y1_loc+1;
            c4logic->frame_y4 = c4logic->frame_y3 +1;
        }
        else {
            c4logic->frame_y1 = c4logic->y1_loc;
            c4logic->frame_y2 = c4logic->y2_loc;
            c4logic->frame_y3 = c4logic->y2_loc+1;
            c4logic->frame_y4 = c4logic->frame_y3 +1;

        }

    }
    
    if((c4logic->y1_loc != c4logic->y2_loc) && (c4logic->x1_loc != c4logic->x2_loc) ){
        if(c4logic->x1_loc<c4logic->x2_loc){
            if(c4logic->y1_loc<c4logic->y2_loc){
                c4logic->frame_x1 = c4logic->x1_loc;
                c4logic->frame_x2 = c4logic->x2_loc;
                c4logic->frame_x3 = c4logic->x1_loc+1;
                c4logic->frame_x4 = c4logic->frame_x3 +1;

                c4logic->frame_y1 = c4logic->y1_loc;
                c4logic->frame_y2 = c4logic->y2_loc;
                c4logic->frame_y3 = c4logic->y1_loc+1;
                c4logic->frame_y4 = c4logic->frame_y3 +1;
            }else{
                c4logic->frame_x1 = c4logic->x1_loc;
                c4logic->frame_x2 = c4logic->x2_loc;
                c4logic->frame_x3 = c4logic->x1_loc+1;
                c4logic->frame_x4 = c4logic->frame_x3 +1;

                c4logic->frame_y1 = c4logic->y1_loc;
                c4logic->frame_y2 = c4logic->y2_loc;
                c4logic->frame_y3 = c4logic->y1_loc-1;
                c4logic->frame_y4 = c4logic->frame_y3 -1;
            }
        }else{
            if(c4logic->y1_loc<c4logic->y2_loc){
                c4logic->frame_x1 = c4logic->x1_loc;
                c4logic->frame_x2 = c4logic->x2_loc;
                c4logic->frame_x3 = c4logic->x1_loc-1;
                c4logic->frame_x4 = c4logic->frame_x3 -1;

                c4logic->frame_y1 = c4logic->y1_loc;
                c4logic->frame_y2 = c4logic->y2_loc;
                c4logic->frame_y3 = c4logic->y1_loc+1;
                c4logic->frame_y4 = c4logic->frame_y3 +1;
            }else{
                c4logic->frame_x1 = c4logic->x1_loc;
                c4logic->frame_x2 = c4logic->x2_loc;
                c4logic->frame_x3 = c4logic->x1_loc-1;
                c4logic->frame_x4 = c4logic->frame_x3 -1;

                c4logic->frame_y1 = c4logic->y1_loc;
                c4logic->frame_y2 = c4logic->y2_loc;
                c4logic->frame_y3 = c4logic->y1_loc-1;
                c4logic->frame_y4 = c4logic->frame_y3 -1;
            }
        }


        /* if(c4logic->x1_loc<c4logic->x2_loc){
            c4logic->frame_x1 = c4logic->x1_loc;
            c4logic->frame_x2 = c4logic->x2_loc;
            c4logic->frame_x3 = c4logic->x1_loc+1;
            c4logic->frame_x4 = c4logic->frame_x3 +1;
        }
        else {
            c4logic->frame_x1 = c4logic->x1_loc;
            c4logic->frame_x2 =c4logic-> x2_loc;
            c4logic->frame_x3 = c4logic->x2_loc+1;
            c4logic->frame_x4 = c4logic->frame_x3 +1;

        }
        if(c4logic->y1_loc<c4logic->y2_loc){
            c4logic->frame_y1 = c4logic->y1_loc;
            c4logic->frame_y2 = c4logic->y2_loc;
            c4logic->frame_y3 = c4logic->y1_loc+1;
            c4logic->frame_y4 = c4logic->frame_y3 +1;
        }
        else {
            c4logic->frame_y1 = c4logic->y1_loc;
            c4logic->frame_y2 = c4logic->y2_loc;
            c4logic->frame_y3 = c4logic->y2_loc+1;
            c4logic->frame_y4 = c4logic->frame_y3 +1;

        }*/



    }

}

void connect4frame::updateUi()
{
    printBoard();
}

connect4frame::~connect4frame()
{
    delete ui;
}
