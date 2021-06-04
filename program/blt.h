#ifndef BLT_H
#define BLT_H

#include <QObject>
#include <QtBluetooth/qbluetoothglobal.h>
#include <QtBluetooth/qbluetoothlocaldevice.h>
#include <QtBluetooth/qbluetoothsocket.h>
#include <QtBluetooth/qbluetoothservicediscoveryagent.h>

class BLT:public QObject
{
    Q_OBJECT

public:
    BLT(QObject *parent = nullptr);

    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QBluetoothLocalDevice *localDevice;
    QBluetoothSocket *socket;

public slots:
    void bltScan();

};

#endif // BLT_H
