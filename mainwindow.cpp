#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdlib>
#include <ctime>
#include <QLabel>
#include <QMovie>
#include "string.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);
    Qt::WindowFlags m_flags = windowFlags();
    setWindowFlags(m_flags|Qt::WindowStaysOnTopHint);
    pet_appearance=new QLabel(this);
    SelectAppearance();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pet_appearance;
}
void MainWindow::SelectAppearance(){
    pet_appearance->resize(175,150);
    pet_appearance->setPixmap(QPixmap(":/resources/static/default.png").scaled(pet_appearance->size()));
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) { //检测到左键按压
        m_dragStartPosition = event->pos(); //记录鼠标位置
        m_isDragging = false;   //设置拖拽状态为否
        //这两个变量我估计应该在头文件中定义后才能使用
         //m_startPos = event->globalPos() ;//- frameGeometry().topLeft();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)  {

    if ((event->buttons() & Qt::LeftButton) && !m_isDragging)
    {
//m_dragStartPosition = event->globalPos();
        QPoint dragDistance = event->pos() - m_dragStartPosition;
        if (dragDistance.manhattanLength()> QApplication::startDragDistance()) // 如果鼠标移动距离超过一定阈值，认为开始拖拽操作
        {
            m_isDragging = true; //设置拖拽状态为是
            //QPoint globalPos = mapToGlobal(event->pos());
                      // QPoint dragDirection = dragDistance;//.normalized();
                       //move(globalPos - dragDirection);
                      // m_dragStartPosition = event->pos();
            //下面是你的代码，应该是用来播放动画和调整位置的
           // QPoint diff = event->globalPos() - m_startPos; //我猜m_startPos应该和m_dragStartPosition的作用是一样的？我没有找到m_startPos是在哪里定义的

              //  move(diff);
            //Qt::WindowFlags m_flags = windowFlags();
            //setWindowFlags(m_flags|Qt::WindowStaysOnTopHint);
           /* if (dragDistance.x() > 0) {
                          m_flags &= ~Qt::LeftToRight;
                         // m_flags |=  Qt::RightToLeft;
                       } else if (dragDistance.x() < 0) {
                          m_flags &= ~Qt::RightToLeft;
                           //m_flags |= Qt::LeftToRight;
                       }
                       if (dragDistance.y() > 0) {
                           //m_flags &= ~Qt::TopToBottom;
                           //flags |= Qt::BottomToTop;
                       } else if (dragDistance.y() < 0) {
                           //m_flags &= ~Qt::BottomToTop;
                           //flags |= Qt::TopToBottom;
                       }*/
         move(event ->pos() + dragDistance);
                QMovie* backgroundMovie = new QMovie(this);

                backgroundMovie = new QMovie(":/resources/dynamic/9f99e657-57ba-4668-aad9-bb921eefc4a8.gif", QByteArray(), this);
                backgroundMovie->setScaledSize(pet_appearance->size());
                connect(backgroundMovie, &QMovie::frameChanged, [=](int frameNumber) {
                    if (frameNumber == backgroundMovie->frameCount() - 1)//currentFrameNumber()：获取当前帧数
                    {
                        backgroundMovie->stop();
                        pet_appearance->setPixmap(QPixmap(":/resources/static/default.png").scaled(pet_appearance->size()));
                    }
                });
            pet_appearance->setMovie(backgroundMovie);
            backgroundMovie->start();
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && m_isDragging) {//从拖拽状态结束左键按压
        // 结束拖拽操作
        m_isDragging = false;
    }
    else if (event->button() == Qt::LeftButton && !m_isDragging) {//非从拖拽状态结束左键按压
        //应该是播放单击动画的代码
        QMovie* backgroundMovie = new QMovie(this);
        srand((int)time(0));
        int i = rand() % 12;
        QString gif[12] = { ":/resources/left_mouse_click/default3.gif",":/resources/left_mouse_click/leftclick9.gif",":/resources/left_mouse_click/leftclick16.gif",":/resources/left_mouse_click/leftclick13.gif",":/resources/left_mouse_click/leftclick14.gif",":/resources/left_mouse_click/leftclick15.gif",":/resources/left_mouse_click/leftclick6.gif",":/resources/left_mouse_click/leftclick11.gif",":/resources/left_mouse_click/leftclick8.gif",":/resources/left_mouse_click/leftclick12.gif",":/resources/left_mouse_click/leftclick17.gif",":/resources/left_mouse_click/leftclick18.gif" };
        backgroundMovie = new QMovie(gif[i], QByteArray(), this);
        backgroundMovie->setScaledSize(pet_appearance->size());
        connect(backgroundMovie, &QMovie::frameChanged, [=](int frameNumber) {
            if (frameNumber == backgroundMovie->frameCount() - 1)//currentFrameNumber()：获取当前帧数
            {
                backgroundMovie->stop();
                pet_appearance->setPixmap(QPixmap(":/resources/static/default.png").scaled(pet_appearance->size()));
            }
            });
        pet_appearance->setMovie(backgroundMovie);
        backgroundMovie->start();
    }
}
