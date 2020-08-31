#ifndef CHOOSELEVELSCENCE_H
#define CHOOSELEVELSCENCE_H

#include <QMainWindow>
#include<playscene.h>
class ChooseLevelScence : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScence(QWidget *parent = nullptr);

    PlayScene * pScene = NULL;
    void paintEvent(QPaintEvent *);

signals:
 void chooseSceneBack();

};

#endif // CHOOSELEVELSCENCE_H
