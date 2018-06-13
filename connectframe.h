#ifndef CONNECTFRAME_H
#define CONNECTFRAME_H

#include <QFrame>

namespace Ui {
class ConnectFrame;
}

class ConnectFrame : public QFrame
{
    Q_OBJECT

public:
    explicit ConnectFrame(QWidget *parent = 0);
    ~ConnectFrame();

signals:
    void bluetoothConnect(QString addr1, QString addr2);

public slots:
    void setDevice(QString addr, QString name);

private slots:
    void on_bl1clear_clicked();

    void on_bl2clear_clicked();

    void on_connect_clicked();

private:
    Ui::ConnectFrame *ui;
};

#endif // CONNECTFRAME_H
