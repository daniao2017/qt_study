#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPainter>
#include<QPixmap>
#include<QDebug>
#include<QPushButton>
#include<mypushbutton.h>
#include<QTimer>
#include<QSound>
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //设置固定大小
    this ->setFixedSize(320,588);
    //设置窗口图片
    this ->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置窗口标题
    this ->setWindowTitle("翻金币小游戏");

    QSound *startSound = new QSound(":/res/TapButtonSound.wav",this);



    //点击退出，退出程序
    connect(ui->actionQuit,&QAction::triggered,[=](){

        this ->close();
    });

  MyPushButton * startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
  startBtn ->setParent(this);
  startBtn ->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);

   chooseScene = new ChooseLevelScence;
  //监听点击事件，并执行特效
  connect(startBtn,&MyPushButton::clicked,[=](){

      startBtn ->zoom1(); //向下跳跃
      startBtn ->zoom2(); //向上跳跃
      startSound->play(); //开始音效
      QTimer::singleShot(500,this,[=](){
          this->hide();
          chooseScene ->setGeometry(this->geometry());
          chooseScene->show();

      });
  });

  connect(chooseScene,&ChooseLevelScence::chooseSceneBack,[=](){
      this ->setGeometry(chooseScene->geometry());
      this ->show();
  });
}
//重写MainScene的PaintEvent事件
void MainScene::paintEvent(QPaintEvent *event){
   //创建画家，指定绘图设备
    QPainter painter(this);
    //创建QPixmap对象
    QPixmap pix;
    //加载图片
    pix.load(":/res/PlayLevelSceneBg.png");
    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //加载标题
    pix.load(":/res/Title.png");
    //缩放图片
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    //绘制标题
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);

}
MainScene::~MainScene()
{
    delete ui;
}

