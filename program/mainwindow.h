#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QBluetoothDeviceDiscoveryAgent>
#include<QBluetoothSocket>
#include<QListWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QBluetoothDeviceDiscoveryAgent *agent = new QBluetoothDeviceDiscoveryAgent;
    QBluetoothSocket *socket;
    QString string;
    bool k = false;

private slots:
    void on_find_clicked();
    void deviceDiscovered(const QBluetoothDeviceInfo &device);
    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_headlights_clicked();
    void on_red_clicked();
    void on_white_clicked();
    void on_speedSlider_sliderMoved(int position);
    void on_robot_clicked();
    void on_front_wheels_clicked();
};

#endif // MAINWINDOW_H
