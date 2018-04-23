#include "xox.h"
#include "ui_xox.h"

XOX::XOX(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::XOX)
{
    ui->setupUi(this);
}

XOX::~XOX()
{
    delete ui;
}

void XOX::onBoardChange(struct packet p){
    ui->a1->setText(QString((char)(p.data.xox.cell_states[0])));
    ui->a2->setText(QString((char)(p.data.xox.cell_states[1])));
    ui->a3->setText(QString((char)(p.data.xox.cell_states[2])));
    ui->b1->setText(QString((char)(p.data.xox.cell_states[3])));
    ui->b2->setText(QString((char)(p.data.xox.cell_states[4])));
    ui->b3->setText(QString((char)(p.data.xox.cell_states[5])));
    ui->c1->setText(QString((char)(p.data.xox.cell_states[6])));
    ui->c2->setText(QString((char)(p.data.xox.cell_states[7])));
    ui->c3->setText(QString((char)(p.data.xox.cell_states[8])));

    ui->a1->setChecked(false);
    ui->a2->setChecked(false);
    ui->a3->setChecked(false);
    ui->b1->setChecked(false);
    ui->b2->setChecked(false);
    ui->b3->setChecked(false);
    ui->c1->setChecked(false);
    ui->c2->setChecked(false);
    ui->c3->setChecked(false);

    switch (p.data.xox.position % 9) {
    case 0:
        ui->a1->setChecked(true);
        break;
    case 1:
        ui->a2->setChecked(true);
        break;
    case 2:
        ui->a3->setChecked(true);
        break;
    case 3:
        ui->b1->setChecked(true);
        break;
    case 4:
        ui->b2->setChecked(true);
        break;
    case 5:
        ui->b3->setChecked(true);
        break;
    case 6:
        ui->c1->setChecked(true);
        break;
    case 7:
        ui->c2->setChecked(true);
        break;
    case 8:
        ui->c3->setChecked(true);
        break;
    }
}
