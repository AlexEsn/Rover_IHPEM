#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QPixmap>
#include "joypad.h"

#include<QtBluetooth>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //joy
    connect(ui->widget, &JoyPad::xChanged, this, [this](float x){
        qDebug() << "x: " << x << " y: " << ui->widget->y();
        socket->write("$");
        x *= 100;
        int out = x;
        std::string tmp = std::to_string(out);
        char const *data = tmp.c_str();
        socket->write(data);
    });


    connect(ui->widget, &JoyPad::yChanged, this, [this](float y){
        socket->write(" ");
        qDebug() << "x: " << ui->widget->x() << " y: " << y;
        y *= 100;
        int out = y;
        std::string tmp = std::to_string(out);
        char const *data = tmp.c_str();
        socket->write(data);
        socket->write(";");
    });


    //bl
    connect(agent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(deviceDiscovered(QBluetoothDeviceInfo)));
    agent->start();
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_find_clicked()
{
    ui->listWidget->clear();
    agent->stop();
    agent->start();
}

void MainWindow::deviceDiscovered(const QBluetoothDeviceInfo &device)
{
    ui->listWidget->addItem(device.address().toString());
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
 string =item->text();
 ui->listWidget->addItem(string);
 static const QString serviceUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB"));
 socket->connectToService(QBluetoothAddress(string), QBluetoothUuid(serviceUuid), QIODevice::ReadWrite);
}

void MainWindow::on_headlights_clicked()
{
    socket->write("$10 -110;");
}

void MainWindow::on_red_clicked()
{
    socket->write("$11 -110;");
}

void MainWindow::on_white_clicked()
{
    socket->write("$12 -110;");
}

void MainWindow::on_speedSlider_sliderMoved(int position)
{
    std::string tmp = std::to_string(position);
    char const *data = tmp.c_str();
    socket->write("$");
    socket->write(data);
    socket->write(" -120;");
}

void MainWindow::on_robot_clicked()
{
    socket->write("$20 -110;");
}

void MainWindow::on_front_wheels_clicked()
{
    socket->write("$30 -110;");
}
