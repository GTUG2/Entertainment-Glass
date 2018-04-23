#include "reader.h"

Reader::Reader(QObject *parent) : QObject(parent)
{
    size = 0;
}

void Reader::setup(QBluetoothSocket *sock){
    s = sock;
}

void Reader::readready() {
    size += s->read((char *)((char *)(&p) + size), sizeof(p) - size);

    if(size == sizeof(p)){
        emit onpacketreceived(p);
        QString qs;
        for(char *t = (char *)&p ; t < (char *)((char *)&p + size) ; ++t){
            qs.append(QString::number((int)*t)).append(" ");
        }
        qDebug() << qs;
        size = 0;
    }
}
