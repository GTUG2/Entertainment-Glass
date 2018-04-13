#include "scanworker.h"

ScanWorker::ScanWorker(){

}

ScanWorker::~ScanWorker(){

}

void ScanWorker::start(){
    /* currently my bluetooth is not working, this should spawn a hcitool scan process and parse its results */
    emit newDeviceFound(QString("AA:BB:CC:DD:EE:FF"), QString("DEV1"));
    emit newDeviceFound(QString("AA:BB:CC:DD:EE:FD"), QString("DEV2"));
    emit newDeviceFound(QString("AA:BB:CC:DD:EE:FE"), QString("DEV3"));
    emit finished();
}

