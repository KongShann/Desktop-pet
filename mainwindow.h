#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>

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
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    Ui::MainWindow *ui;

    QLabel* pet_appearance; //外观显示Lable指针
    QLabel* label;
    QPushButton* select_appearance_btn; //切换外观按钮指针

    bool m_dragging = false;

    QPoint m_startPos;
};
#endif // MAINWINDOW_H
