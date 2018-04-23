#ifndef XOX_H
#define XOX_H

#include <QMainWindow>
#include "common.h"

namespace Ui {
class XOX;
}

class XOX : public QMainWindow
{
    Q_OBJECT

public:
    explicit XOX(QWidget *parent = 0);
    ~XOX();

public slots:
    void onBoardChange(struct packet p);

private:
    Ui::XOX *ui;
};

#endif // XOX_H
