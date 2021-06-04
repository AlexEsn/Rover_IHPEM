#include "blt.h"


BLT::BLT(QObject *parent) : QObject(parent)
{

    discoveryAgent = new QBluetoothDeviceDiscoveryAgent();
    localDevice = new QBluetoothLocalDevice();
    socket  =new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
}

void BLT::bltScan(){

    if(localDevice->hostMode() == QBluetoothLocalDevice::HostPoweredOff){
        localDevice->powerOn();
    }
    discoveryAgent->setInquiryType(QBluetoothDeviceDiscoveryAgent::GeneralUnlimitedInquiry);
    discoveryAgent->start();

}
