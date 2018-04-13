#include <QProcess>
#include <QObject>

#ifndef RFCOMM_H
#define RFCOMM_H

class RFComm : public QObject
{
    Q_OBJECT
public:
    RFComm(const QString &dev, const QString &addr);

public slots:
    void connect();
    void close();
signals:
    void connected();
    void failed();
private:
    QProcess rfcomm;
};

#endif // RFCOMM_H
