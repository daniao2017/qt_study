#include "chooselevelscence.h"
#include<QMenu>
#include<QMenuBar>
#include<QAction>
#include<QPainter>
#include<QPixmap>
#include<mypushbutton.h>
#include<QTimer>
#include<QLabel>
#include<QString>
#include<playscene.h>
#include<QSound>
ChooseLevelScence::ChooseLevelScence(QWidget *parent) : QMainWindow(parent)
{
    //设置固定大小
    this ->setFixedSize(320,588);
    //设置窗口图片
    this ->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置窗口标题
    this ->setWindowTitle("选择关卡场景");

    //创建菜单栏
    QMenuBar * bar = this ->menuBar();
    this ->setMenuBar(bar);
    //创建开始菜单
    QMenu * startMenu = bar ->addMenu("开始");
    //创建按钮菜单项
    QAction * quitAction = startMenu->addAction("退出");
    //点击退出，退出游戏
    connect(quitAction,&QAction::triggered,[=](){
         this ->close();
    });
    //选择关卡按钮音效
     QSound *chooseSound = new QSound(":/res/TapButtonSound.wav",this);
     //返回按钮音效
     QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);

    //返回按钮
    MyPushButton * closeBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    closeBtn ->setParent(this);
    closeBtn -> move(this->width()-closeBtn->width(),this->height()-closeBtn->height());

    //返回按钮功能实现
    connect(closeBtn,&MyPushButton::clicked,[=](){
        QTimer::singleShot(500,this,[=](){
            this->hide();
            //触发自身信号
            emit this ->chooseSceneBack();
        });
    });

    //创建关卡按钮
    for(int i =0;i<20;i++){
        MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn ->setParent(this);
        menuBtn ->move(25+(i%4)*70,130+(i/4)*70);

        //按钮上显示的文字
        QLabel * label = new QLabel;
        label ->setParent(this);
        label ->setFixedSize(menuBtn->width(),menuBtn->height());
        label ->setText(QString::number(i+1));
        //设置居中
        label ->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //移动
        label->move(25 + (i%4)*70 , 130+ (i/4)*70);
        //鼠标事件穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents,true);
        //监听选择关卡按钮的信号槽
        connect(menuBtn,&MyPushButton::clicked,[=](){
           if(pScene ==NULL){
               this ->hide();
               pScene = new PlayScene(i+1);
               pScene ->setGeometry(this->geometry());
               chooseSound->play();
               pScene ->show();

             //监听信号
            connect(pScene,&PlayScene::chooseSceneBack,[=](){
                this->setGeometry(pScene->geometry());
                  this->show();
                  backSound->play();
                  delete pScene;
                  pScene = NULL;
                              });
           }
        });



    }
}
void ChooseLevelScence::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);


}
