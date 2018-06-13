#ifndef PINGBOSSFRAME_H
#define PINGBOSSFRAME_H

#include "common.h"

#include <QFrame>
#include <QLabel>

namespace Ui {
class PingBossFrame;
}

class PingBossFrame : public QFrame
{
    Q_OBJECT

public:
    explicit PingBossFrame(QWidget *parent = 0);
    ~PingBossFrame();

signals:
    void changeUIRequest(int);

public slots:
    void updateUI(pingboss p);
    void resetUI();

private:
    Ui::PingBossFrame *ui;
    QLabel *bullets[20];
};

#endif // PINGBOSSFRAME_H
