#include "rfcomm.h"
#include <QDebug>

void RFComm::cfinished(int exitCode, QProcess::ExitStatus exitStatus){
    switch (exitStatus) {
    case QProcess::NormalExit:
        if(exitCode == 0){
            emit cleaned(QString(rfcomm.readAll()));
        }else{
            emit failed(exitCode);
        }
        break;
    case QProcess::CrashExit:
        emit crashed();
        break;
    default:
        std::cerr << "[RFCOMM][CFINISHED] Undocumented value: " << exitStatus << std::endl;
        break;
    }
    qDebug() << rfcomm.readAll();
}

void RFComm::closeConnection(){
    qDebug() << "procid: " << rfcomm.processId();
}

void RFComm::conn(const QString &dev, const QString &addr){
    QStringList args;
    args << "-S" << "/usr/bin/rfcomm connect " + dev + " " + addr;
    connect(&rfcomm, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(cfinished(int, QProcess::ExitStatus)));

    rfcomm.start("/usr/bin/sudo", args);
    rfcomm.write("SiyahaS\nDarkytys94\n");

    /* TODO Create another thread to wait for this child specifically.
     * If the connection never starts the process quits with an error code.*/
}
