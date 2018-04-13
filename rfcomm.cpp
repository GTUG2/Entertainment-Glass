#include "rfcomm.h"

RFComm::RFComm(const QString &dev, const QString &addr)
{
    QStringList args;
    args << "-c" << "sudo rfcomm connect " + dev + " " + addr;
    rfcomm.start("/bin/sh", args);

    /* TODO Create another thread to wait for this child specifically.
     * If the connection never starts the process quits with an error code.*/
}

void RFComm::connect(){

}

void RFComm::close(){

}
