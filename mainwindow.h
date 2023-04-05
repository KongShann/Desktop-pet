#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SelectAppearance(); //切换外观
private:
    Ui::MainWindow *ui;

    QLabel* pet_appearance; //外观显示Lable指针

    QPushButton* select_appearance_btn; //切换外观按钮指针
    QPushButton* click_to_shopButton;//进入商店按扭

    void gotoshop();
};
#endif // MAINWINDOW_H
