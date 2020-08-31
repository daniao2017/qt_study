#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include<mycoin.h>
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(QWidget *parent = nullptr);

    PlayScene *pScene = NULL;
    //成员变量 记录关卡索引
     int levalIndex;

     PlayScene(int index);
    void paintEvent(QPaintEvent *);
    MyCoin * coinBtn[4][4]; //金币按钮数组
    int gameArray[4][4]; //二维数组数据
     bool isWin = true; //是否胜利

signals:
     void chooseSceneBack();
};

#endif // PLAYSCENE_H
