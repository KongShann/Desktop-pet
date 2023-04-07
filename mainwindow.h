

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QMovie>
#include <QRandomGenerator>
#include <QMouseEvent>

#include "petobjects_struct.h"
#include "appchoosewindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void OnAppearanceChanged(int label_index);
    void OnAppChooseBtnClicked();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void InitButton(); //初始化按钮

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent* event); //用于实现单击和拖动事件处理


private:
    Ui::MainWindow *ui;

    QVector<PetAppearance> *owned_pet_appearances; //已拥有的宠物外观
    PetAppearance displayed_pet_appearance;//正在显示的外观
    QVector<QString> *pet_movements;//宠物动作动画文件路径数组指针

    QTimer* petmovement_timer;//宠物动作计时器

    QLabel* pet_displayed_label; //外观显示Lable指针

    QPushButton* appchoose_btn; //切换外观按钮指针

    AppChooseWindow* appchoose_win; //切换外观窗口

    QPoint petlabel_dragstartposition;//显示窗口开始被拖拽时的位置
    bool  petlabel_isdragging;//显示窗口是否被拖拽

};
#endif // MAINWINDOW_H

