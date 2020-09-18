#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //user
    system_init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*-------------------------------------
 *        funtions
 * -----------------------------------*/

void MainWindow::system_init(){
    //port config
    global_port.setParity(QSerialPort::NoParity);
    global_port.setDataBits(QSerialPort::Data8);
    global_port.setStopBits(QSerialPort::OneStop);

    //connect
    connect(ui->btn_open,&QPushButton::clicked,this,&MainWindow::btn_open_port);
    connect(ui->btn_send_data,&QPushButton::clicked,this,&MainWindow::btn_open_port);
    connect(&global_port,&QSerialPort::readyRead,this,&MainWindow::receive_data);
    connect(ui->btn_close,&QPushButton::clicked,this,&MainWindow::btn_close_port);

    //fix
     this->setFixedSize( this->width (),this->height ());



}

/*------------------------------------
 *           slot
 * ---------------------------------*/

void MainWindow::btn_open_port(bool){

    //qDebug()<< ui->cmb_port_name->currentIndex();
    /*----------------------port---------------*/
    switch (ui->cmb_port_name->currentIndex()) {
    case 0 :
        global_port.setPortName("COM1");
        break;
    case 1 :
        global_port.setPortName("COM2");
        break;
    case 2 :
        global_port.setPortName("COM3");
        break;
    case 3 :
        global_port.setPortName("COM4");
        break;
    case 4 :
        global_port.setPortName("COM5");
        break;
    case 5 :
        global_port.setPortName("COM6");
        break;
    case 6 :
        global_port.setPortName("COM7");
        break;
    default:
        global_port.setPortName("COM8");
        break;
    }
    /*----------------baud_rate--------------------*/
    switch (ui->cmb_baud_rate->currentIndex()) {
    case 0 :
        global_port.setBaudRate(QSerialPort::Baud115200);
        break;
    case 1 :
        global_port.setBaudRate(QSerialPort::Baud57600);
        break;
    case 2 :
        global_port.setBaudRate(QSerialPort::Baud38400);
        break;
    case 3 :
        global_port.setBaudRate(QSerialPort::Baud19200);
        break;
    case 4 :
        global_port.setBaudRate(QSerialPort::Baud9600);
        break;
    case 5 :
        global_port.setBaudRate(QSerialPort::Baud4800);
        break;
    case 6 :
        global_port.setBaudRate(QSerialPort::Baud2400);
        break;
    case 7 :
        global_port.setBaudRate(QSerialPort::Baud1200);
        break;
    default:
        global_port.setBaudRate(QSerialPort::Baud9600);
        break;
   }

    /*--------------------open---------------------*/
    global_port.open(QIODevice::ReadWrite);
    ui->lab_status->setText("Connected");


}
/*---------------sending data -------------------*/
void MainWindow::btn_send_data(bool){

    QString data = ui->lineEdit->text();
    QByteArray array = data.toLatin1();
    global_port.write(array);

}

/*------------------receive data -----------------*/
void MainWindow::receive_data(){
    QByteArray array = global_port.readAll();
    qDebug() <<array;
    if(ui->checkBox->checkState() == Qt::Checked){
           ui ->plainTextEdit ->insertPlainText(QString(array.toHex(' ')).append(' '));
    }
    else{
         ui ->plainTextEdit ->insertPlainText(QString(array));
    }

}

/*-----------------------close port----------------------*/
void MainWindow::btn_close_port(bool){
    global_port.close();
    ui->lab_status->setText("Disconnected");
}


