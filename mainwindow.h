#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QDialog>
#include <QVBoxLayout>
#include <QListWidget>
#include <QMovie>
#include "petobjects_struct.h"
#include "appchoosewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(int hunger READ hunger WRITE setHunger NOTIFY hungerChanged)

public slots:
    void OnAppearanceChanged(int label_index);
    void OnAppChooseBtnClicked();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void SelectAppearance(); //切换外观
    void InitButton();
    int hunger() const;
    void setHunger(int hunger);
signals:
     void hungerChanged(int hunger);
private slots:
      void feedPet();
      void increaseHunger();
       void showFoodList();
       void startEating();
       void stopEating();
       void HungerChangeAppearance();//根据饥饿值改变宠物外观


protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    Ui::MainWindow *ui;
    int m_hunger;
    QLabel* pet_displayed_label; //外观显示Lable指针
    QLabel *m_hungerLabel;//显示饥饿值指针
    QPushButton* appchoose_btn; //切换外观按钮指针
    QPushButton* m_feedButton;
    QTimer *m_hungerTimer;//饥饿值增长指针
    QMovie *m_eatingMovie;//宠物进食指针
    QVector<PetAppearance> *owned_pet_appearances;
    PetAppearance displayed_pet_appearance;
    AppChooseWindow* appchoose_win; //切换外观窗口

};
#endif // MAINWINDOW_H




