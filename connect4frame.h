#ifndef CONNECT4FRAME_H
#define CONNECT4FRAME_H

#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include "connect4logic.h"


#define BOARD_SIZE 42
namespace Ui {
class connect4frame;
}

class connect4frame : public QFrame
{
    Q_OBJECT

public:
    explicit connect4frame(connect4logic *c4logic_param, QWidget *parent = 0);
    ~connect4frame();
    void printBoard();
    void roundWonSet();
public slots:
    void updateUi();

signals:
    void changeUIRequest(int);

private:
    Ui::connect4frame *ui;
    connect4logic *c4logic;
    QLabel *lbls[BOARD_SIZE];
};


#endif // CONNECT4FRAME_H
