

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
    void mousePressEvent(QMouseEvent *event);//鼠标单击实现互动
    void mouseMoveEvent(QMouseEvent *event);//鼠标拖动实现互动
    void mouseReleaseEvent(QMouseEvent* event);

private:
    Ui::MainWindow *ui;

    QLabel* pet_appearance; //外观显示Lable指针

    QPushButton* select_appearance_btn; //切换外观按钮指针

    QPoint m_dragStartPosition;
     QPoint diff;
    bool  m_isDragging;
};
#endif // MAINWINDOW_H

