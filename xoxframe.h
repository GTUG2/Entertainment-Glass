#ifndef XOXFRAME_H
#define XOXFRAME_H

#include <QFrame>
#include <QLabel>
#include <string>
#include "xoxlogic.h"

namespace Ui {
class XOXFrame;
class XOXLogic;
}

class XOXFrame : public QFrame
{
    Q_OBJECT

public:
    explicit XOXFrame(QWidget *parent = 0);
    ~XOXFrame();
    static QString *styleSheets;

signals:
    void changeUIRequest(int);

public slots:
    void updateUI(xox p);
    void resetUI();

private:
    Ui::XOXFrame *ui;
    XOXLogic *xox_logic_ptr;
    QLabel *labels[9];
    int styleSheetProps[9][2]; // [*][0]: x/o/empty [*][1]: cursor/win/normal
    int last;
    int lastv;
};

#endif // XOXFRAME_H
