#ifndef READER_H
#define READER_H

#include <QObject>
#include "common.h"
#include <QBluetoothSocket>

class Reader : public QObject
{
    Q_OBJECT
public:
    explicit Reader(QObject *parent = nullptr);
    void setup(QBluetoothSocket *sock);
signals:
    void onpacketreceived(struct packet p);
public slots:
    void readready();
private:
    struct packet p;
    qint64 size;
    QBluetoothSocket *s;
};

#endif // READER_H
