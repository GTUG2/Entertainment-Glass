#include "xoxframe.h"
#include "ui_xoxframe.h"
#include <QDebug>

QString* XOXFrame::styleSheets = new QString[9] {
    QString("image: url(://images/xox/empty.svg);"), // normal empty
    QString("image: url(://images/xox/x.svg);"), // normal x
    QString("image: url(://images/xox/o.svg);"), // normal o
    QString("image: url(://images/xox/empty_cursor.svg);"), // cursor empty
    QString("image: url(://images/xox/x_cursor.svg);"), // cursor X
    QString("image: url(://images/xox/o_cursor.svg);"), // cursor o
    QString("image: url(://images/xox/empty_win.svg);"), // win empty
    QString("image: url(://images/xox/x_win.svg);"), // win x
    QString("image: url(://images/xox/o_win.svg);") // win o
};

XOXFrame::XOXFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::XOXFrame)
{    
    ui->setupUi(this);
    labels[0] = ui->l0;
    labels[1] = ui->l1;
    labels[2] = ui->l2;
    labels[3] = ui->l3;
    labels[4] = ui->l4;
    labels[5] = ui->l5;
    labels[6] = ui->l6;
    labels[7] = ui->l7;
    labels[8] = ui->l8;
    for(int i = 0 ; i < 9 ; ++i)
        styleSheetProps[i][0] = styleSheetProps[i][1] = 0;
    last = 0;
    lastv = 0;
    //XOXFrame::styleSheets = {QString(""), QString("image: url(://images/X.png);"), QString("image: url(://images/O.png);"), QString("background-color: rgb(0,0,255);"), QString("image: url(://images/X.png);background-color: rgb(0,0,255);"), QString("image: url(://images/O.png);background-color: rgb(0,0,255);"), QString("background-color: rgb(0,255,0);"), QString("image: url(://images/X.png);background-color: rgb(0,255,0);"), QString("image: url(://images/O.png);background-color: rgb(0,255,0);")};

}

void XOXFrame::updateUI(struct xox p){
    QLabel *lbl;

    if(p.cursor < 10 && p.cursor >= 0){
        lastv = styleSheetProps[p.cursor][1];
        styleSheetProps[p.cursor][1] = 1;
        styleSheetProps[last][1] = lastv;
        last = p.cursor;
    }

    if(p.position < 10 && p.position >= 0)
        styleSheetProps[p.position][0] = p.stamp;

    if(p.winner[0] < 10 && p.winner[0] >= 0){
        styleSheetProps[p.winner[0]][1] = styleSheetProps[p.winner[1]][1] = styleSheetProps[p.winner[2]][1] = 2;
    }

    for(int i = 0 ; i < 9 ; ++i){
        QString style;
        if(styleSheetProps[i][0] == 0 && styleSheetProps[i][1] == 0){
            // normal empty
            style = styleSheets[0];
        }else if(styleSheetProps[i][0] == 1 && styleSheetProps[i][1] == 0){
            // normal X
            style = styleSheets[1];
        }else if(styleSheetProps[i][0] == 2 && styleSheetProps[i][1] == 0){
            // normal O
            style = styleSheets[2];
        }else if(styleSheetProps[i][0] == 0 && styleSheetProps[i][1] == 1){
            // cursor empty
            style = styleSheets[3];
        }else if(styleSheetProps[i][0] == 1 && styleSheetProps[i][1] == 1){
            // cursor X
            style = styleSheets[4];
        }else if(styleSheetProps[i][0] == 2 && styleSheetProps[i][1] == 1){
            // cursor O
            style = styleSheets[5];
        }else if(styleSheetProps[i][0] == 0 && styleSheetProps[i][1] == 2){
            // win empty
            style = styleSheets[6];
        }else if(styleSheetProps[i][0] == 1 && styleSheetProps[i][1] == 2){
            // win X
            style = styleSheets[7];
        }else if(styleSheetProps[i][0] == 2 && styleSheetProps[i][1] == 2){
            // win O
            style = styleSheets[8];
        }
        labels[i]->setStyleSheet(style);
    }
}

void XOXFrame::resetUI()
{
    for(int i = 0 ; i < 9 ; ++i){
        styleSheetProps[i][0] = styleSheetProps[i][1] = 0;
    }
    updateUI({10,0,10,0,{10,10,10},0});
}

XOXFrame::~XOXFrame()
{
    delete ui;
}
