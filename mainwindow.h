﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QDialog>
#include <QVBoxLayout>
#include <QListWidget>
#include <QMovie>
#include <QRandomGenerator>
#include <QMouseEvent>

#include "petobjects_struct.h"
#include "appchoosewindow.h"
#include "shopdress.h"
#include "foodshop.h"
#include "alarmclock.h"
#include "calendarwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(int GetHunger READ GetHunger WRITE SetHunger NOTIFY HungerChanged)

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void InitButton(); //初始化按钮
    void InitHungerSystem();
    void InitPetmovementMovies();
    int GetHunger() const;
    void SetHunger(int GetHunger);

signals:
    void HungerChanged(int GetHunger);

private slots:
    void OnAppearanceChanged(int label_index);
    void OnAppChooseBtnClicked();
    void FeedPet();
    void IncreaseHunger();
    void OnFeedPetBtnClicked();
    void RefreshAppearance();//根据饥饿值改变宠物外观
    void OnEnterShopBtnClicked();
    void OnEnterDailyFunctionBtnClicked();
    void OnEnterAppShopBtnClicked();
    void OnEnterFoodShopBtnClicked();
    void OnEnterAlarmClockBtnClicked();
    void OnEnterCalendarBtnClicked();

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;    //用于实现鼠标进入窗口时显示饥饿值
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent* event) override; //用于实现单击和拖动事件处理

private:
    Ui::MainWindow *ui;
    int pet_hunger;//饥饿值
    PetAppearance displayed_pet_appearance;//正在显示的外观
    QVector<QString> *pet_movements;//宠物动作动画文件路径数组指针
    QTimer *petmovement_timer;//宠物动作计时器指针
    QTimer *pethunger_timer;//饥饿值增长计时器指针
    QLabel *pet_displayed_label; //外观显示Lable指针
    QLabel *hunger_displayed_label;//显示饥饿值Lable指针
    QPushButton *appchoose_btn; //切换外观按钮指针
    QPushButton *feedpet_btn; //喂食宠物按钮指针
    QMovie *peteating_movie;//宠物进食动画指针
    AppChooseWindow* appchoose_win; //切换外观窗口
    QPushButton* entershop_btn;//进入商店按扭指针
    QPushButton* enterappshop_btn;//装饰商店
    QPushButton* enterfoodshop_btn;//食物商店
    QPushButton* enteralarmclock_btn;//闹钟设置
     QPushButton* entercalendar_btn;//日历设置
    QPushButton* enterdailyfunc_btn;//日常功能
    QVector<PetAppearance> *owned_pet_appearances; //已拥有的宠物外观
    QVector<Food> *owned_pet_food;//背包
    QVector<PetAppearance> *not_owned_pet_appearances;//未拥有的宠物外观
    QVector<int> *point;//余额
    QPoint petlabel_dragstartposition;//显示窗口开始被拖拽时的位置
    bool  petlabel_isdragging;//显示窗口是否被拖拽
    alarmclock *myclock;
    QPushButton *calenBtn;//日历按钮
    CalendarWidget* m_calendarWidget;

};
#endif // MAINWINDOW_H









