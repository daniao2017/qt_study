#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H
#include<QPushButton>
#include <QWidget>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QWidget *parent = nullptr);

    //normalImg 代表正常显示的图片
    //pressImg 代表按下后显示的图片,默认为空
    MyPushButton(QString normalImg,QString pressImg="");
    QString normalImgPath; //默认显示图片的位置
    QString preessdImgPath; //按下后显示图片路径
    void zoom1();
    void zoom2();
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:

};

#endif // MYPUSHBUTTON_H
