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
        QPoint dragDistance = event->globalPos() - m_dragStartPosition;
        if (dragDistance.manhattanLength()> QApplication::startDragDistance())
        {
           m_isDragging = true; //设置拖拽状态为是
           QPoint diff = event->globalPos() - m_dragStartPosition;
           move(diff);

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
    else if((event->buttons() & Qt::LeftButton) && m_isDragging)
    {
        QPoint diff = event->globalPos() - m_dragStartPosition;
        move(diff);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && m_isDragging) {
        // 结束拖拽操作
        m_isDragging = false;
        // 这里结束循环，并且停止播放
    }
    else if (event->button() == Qt::LeftButton && !m_isDragging) {
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
