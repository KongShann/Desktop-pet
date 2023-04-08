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
    pet_appearance=new QLabel(this);//已改名
    SelectAppearance();//已弃用

}

MainWindow::~MainWindow()
{
    delete ui;
    delete pet_appearance;//已改名
}
void MainWindow::SelectAppearance(){
    pet_appearance->resize(175,150);
    pet_appearance->setPixmap(QPixmap(":/resources/static/default.png").scaled(pet_appearance->size()));
}
//已弃用的部分

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) { //检测到左键按压
        m_dragStartPosition = event->pos(); //记录鼠标位置
        m_isDragging = false;   //设置拖拽状态为否

    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)  {


    if ((event->buttons() & Qt::LeftButton) && !m_isDragging) //左键按压移动还未进入拖动
    {
        QPoint dragDistance = event->globalPos() - m_dragStartPosition;
        if (dragDistance.manhattanLength()> QApplication::startDragDistance()) //判断是否进入拖动
        {
           m_isDragging = true; //设置拖拽状态为是
           QPoint diff = event->globalPos() - m_dragStartPosition;
           move(diff);


/*
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
  {
      if (event->button() == Qt::LeftButton) {
          m_dragging = false;
           pet_appearance->setPixmap(QPixmap(":/resources/static/default.png").scaled(pet_appearance->size()));
      }
  }*/

           QMovie* backgroundMovie = new QMovie(this);
           backgroundMovie = new QMovie(":/resources/dynamic/mouse_dragging.gif", QByteArray(), this);
           backgroundMovie->setScaledSize(pet_appearance->size());//合并后需要修改

           pet_appearance->setMovie(backgroundMovie);//合并后需要修改
           backgroundMovie->start();

        }
    }
    else if((event->buttons() & Qt::LeftButton) && m_isDragging) //已进入拖动且继续移动鼠标
    {
        QPoint diff = event->globalPos() - m_dragStartPosition;
        move(diff);
    }

}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && m_isDragging) { //左键释放结束拖动
        m_isDragging = false;
        pet_appearance->setPixmap(QPixmap(":/resources/static/default.png").scaled(pet_appearance->size()));//合并后需要修改
    }
    else if (event->button() == Qt::LeftButton && !m_isDragging) { //左键释放时还未进入拖动，判断为点击
        QMovie* backgroundMovie = new QMovie(this);
        srand((int)time(0));
        int i = rand() % 12;
        QString gif[12] = { ":/resources/left_mouse_click/default3.gif",
                            ":/resources/left_mouse_click/leftclick9.gif",
                            ":/resources/left_mouse_click/leftclick16.gif",
                            ":/resources/left_mouse_click/leftclick13.gif",
                            ":/resources/left_mouse_click/leftclick14.gif",
                            ":/resources/left_mouse_click/leftclick15.gif",
                            ":/resources/left_mouse_click/leftclick6.gif",
                            ":/resources/left_mouse_click/leftclick11.gif",
                            ":/resources/left_mouse_click/leftclick8.gif",
                            ":/resources/left_mouse_click/leftclick12.gif",
                            ":/resources/left_mouse_click/leftclick17.gif",
                            ":/resources/left_mouse_click/leftclick18.gif" };
        backgroundMovie = new QMovie(gif[i], QByteArray(), this);
        backgroundMovie->setScaledSize(pet_appearance->size());//合并后需要修改
        connect(backgroundMovie, &QMovie::frameChanged, [=](int frameNumber) {
            if (frameNumber == backgroundMovie->frameCount() - 1)//currentFrameNumber()：获取当前帧数
                {
                    backgroundMovie->stop();
                    pet_appearance->setPixmap(QPixmap(":/resources/static/default.png").scaled(pet_appearance->size()));//合并后需要修改
                }
            });
        pet_appearance->setMovie(backgroundMovie);//合并后需要修改
        backgroundMovie->start();
    }
}

