#include <QProcess>
#include <QObject>
#include "iostream"
#include "unistd.h"
#include "signal.h"

#ifndef RFCOMM_H
#define RFCOMM_H

class RFComm : public QObject
{
    Q_OBJECT
public:
    RFComm(QObject *parent = Q_NULLPTR): QObject(parent) {}

public slots:
    void conn(const QString &dev, const QString &addr);
    void closeConnection();
    void cfinished(int exitCode, QProcess::ExitStatus exitStatus);

signals:
    void connected();
    void failed(int exitCode);
    void cleaned(const QString &out);
    void crashed();
private:
    QProcess rfcomm;
};

#endif // RFCOMM_H
