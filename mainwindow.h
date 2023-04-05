#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include<QTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(int hunger READ hunger WRITE setHunger NOTIFY hungerChanged)

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SelectAppearance(); //切换外观
    int hunger() const;
     void setHunger(int hunger);
signals:
     void hungerChanged(int hunger);
private slots:
      void feedPet();
       void increaseHunger();
protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    Ui::MainWindow *ui;
     int m_hunger;
    QLabel* pet_appearance; //外观显示Lable指针
    QLabel *m_hungerLabel;//显示饥饿值指针
    QPushButton* select_appearance_btn; //切换外观按钮指针
    QPushButton *m_feedButton;//喂食按钮指针
     QTimer *m_hungerTimer;//饥饿值增长指针
};
#endif // MAINWINDOW_H




