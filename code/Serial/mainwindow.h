#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
/*-----------user-----------*/
//port
#include<QSerialPort>
//debug
#include<QDebug>
/*-------------------------*/
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    //button
    void btn_open_port(bool);
    void btn_send_data(bool);
    void btn_close_port(bool);

    //receive_data
    void receive_data();

private:
    Ui::MainWindow *ui;
    /*----------funtion-----------*/
    void system_init();
    /*----------variable----------*/
    QSerialPort global_port ;
};
#endif // MAINWINDOW_H
