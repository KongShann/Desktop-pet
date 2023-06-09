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
#include <QSettings>
#include <QApplication>
#include <QVariant>


#include "petobjects_struct.h"
#include "appchoosewindow.h"
#include "shopdress.h"
#include "foodshop.h"
#include "alarmclock.h"
#include "calendarwidget.h"
#include "settingswindow.h"
#include "taskwindow.h"
#include "game.h"

#define hungerlevel1 60
#define hungerlevel2 80

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
    void InitSettings();
    void InitDisplayedLabel();
    void InitObjects();
    void InitTaskSys();
    int GetHunger() const;
    void SetHunger(int GetHunger);
    void RefreshButtons();

signals:
    void HungerChanged(int GetHunger);
    void HungerLevelCritical();

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
    void OnEnterSettingsWindowBtnClicked();
    void OnEnterAlarmClockBtnClicked();
    void OnEnterGameBtnClicked();
    void showPetTalk();
    void OnEnterTaskWindowBtnClicked();
    void hiddenshowPetTalk();
    void hidePetTalk();
    void CleanSystem();
    void DecreaseClean();
    void OnExitBtnClicked();
    void OnEnterCalendarBtnClicked();
    void OnCleanButtonClicked();//清洁按钮

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;    //用于实现鼠标进入窗口时显示饥饿值
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent* event) override; //用于实现单击和拖动事件处理
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::MainWindow *ui;
    int pet_hunger;//饥饿值
    PetAppearance displayed_pet_appearance;//正在显示的外观
    QVector<QString> *pet_movements;//宠物动作动画文件路径数组指针
    QTimer *petmovement_timer;//宠物动作计时器指针
    QTimer *pethunger_timer;//饥饿值增长计时器指针
    QTimer *m_talkTimer;//非主动下宠物游戏计时器
    QTimer *m_talkTimer2;
    QLabel *pet_displayed_label; //外观显示Lable指针
    QLabel *hunger_displayed_label;//显示饥饿值Lable指针
    PushLabel *m_petTalkLabel;//非主动下宠物请求游戏
    QPushButton *appchoose_btn; //切换外观按钮指针
    QPushButton *feedpet_btn; //喂食宠物按钮指针
    QPushButton *exit_btn;//结束程序按钮指针
    QMovie *peteating_movie;//宠物进食动画指针
    QMovie *petwantplay_movie;//宠物想玩动画指针
    AppChooseWindow* appchoose_win; //切换外观窗口
    SettingsWindow* settings_win; //选择设置窗口
    TaskWindow* task_win; //任务窗口
    QPushButton* entershop_btn;//进入商店按扭指针
    QPushButton* enterappshop_btn;//装饰商店
    QPushButton* enterfoodshop_btn;//食物商店
    QPushButton* enteralarmclock_btn;//闹钟设置
    QPushButton* entercalendar_btn;//日历设置
    QPushButton* enterdailyfunc_btn;//日常功能
    QPushButton* entersettingswin_btn;
    QPushButton* entertaskwin_btn;
    QVector<PetAppearance> *owned_pet_appearances; //已拥有的宠物外观
    QVector<PetAppearance> *pet_appearances; //所有宠物外观
    QPushButton* entergame_btn;//进入游戏指针
    QVector<Food> *owned_pet_food;//背包
    QVector<PetAppearance> *not_owned_pet_appearances;//未拥有的宠物外观
    int point;//余额
    QVector<Task> *tasklist;
    QPoint petlabel_dragstartposition;//显示窗口开始被拖拽时的位置
    bool  petlabel_isdragging;//显示窗口是否被拖拽
    alarmclock *myclock;
    CalendarWidget* m_calendarWidget;
    bool screenedge_isattached_left; // 标识窗口是否吸附在屏幕边缘
    bool screenedge_isattached_right;
    QRect screen_geometry; // 屏幕的几何尺寸
    QList<QWidget*> widgetsToHide; // 需要隐藏的所有按钮
    int cleanvalue;//清洁值
    QLabel *dirtyImageLabel;//肮脏图片指针
    QTimer *dirty_timer;//清洁度计时器指针
    QMovie *petwashing_movie;//宠物洗澡动画指针
    QPushButton *wash_btn;//洗澡按钮
    QSettings *user_settings;//储存用户配置
    QVector<int> id_owned_apps,id_not_owned_apps;
    QVector<int> num_owned_food;
    QVector<int> progress_of_tasks;
    QVector<bool> if_finished_tasks;
    QPoint window_position;
    QSize window_size;
    bool state_of_feedsys;
    bool state_of_tasksys;
    bool s_state_of_feedsys;
    bool s_state_of_tasksys;
    int frequency_of_interact;
    bool show_buttons;
};
#endif // MAINWINDOW_H




