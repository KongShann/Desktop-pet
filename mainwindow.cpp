#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMovie>
#include <cstdlib>
#include <ctime>
#include <QLabel>
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
    delete label;
    delete pet_appearance;
}
void MainWindow::SelectAppearance(){
    pet_appearance->resize(175,150);
    pet_appearance->setPixmap(QPixmap(":/resources/static/default.png").scaled(pet_appearance->size()));
}

void MainWindow::mousePressEvent(QMouseEvent *event)  {
        // 记录鼠标按下时的位置
    if (event->button() == Qt::LeftButton) {
               m_dragging = true;
               m_startPos = event->globalPos() - frameGeometry().topLeft();
               QMovie *backgroundMovie=new QMovie(this);

               backgroundMovie = new QMovie(":/resources/dynamic/9f99e657-57ba-4668-aad9-bb921eefc4a8.gif",QByteArray(),this);
               backgroundMovie->setScaledSize(pet_appearance->size());
               connect(backgroundMovie, &QMovie::frameChanged, [=](int frameNumber){
               if(frameNumber== backgroundMovie->frameCount() -1 )//currentFrameNumber()：获取当前帧数
               {
                  backgroundMovie->stop();
                  pet_appearance->setPixmap(QPixmap(":/resources/static/default.png").scaled(pet_appearance->size()));
               }
               });
               pet_appearance->setMovie(backgroundMovie);
               backgroundMovie->start();


     //pet_appearance->setPixmap(QPixmap(":/resources/dynamic/9f99e657-57ba-4668-aad9-bb921eefc4a8.gif").scaled(pet_appearance->size()));
           }
    }

void MainWindow::mouseMoveEvent(QMouseEvent *event)  {
        // 移动窗口位置
    if (m_dragging) {
                move(event->globalPos() - m_startPos);
                QMovie *backgroundMovie=new QMovie(this);

                backgroundMovie = new QMovie(":/resources/dynamic/9f99e657-57ba-4668-aad9-bb921eefc4a8.gif",QByteArray(),this);
                backgroundMovie->setScaledSize(pet_appearance->size());
                connect(backgroundMovie, &QMovie::frameChanged, [=](int frameNumber){
                if(frameNumber== backgroundMovie->frameCount() -1 )//currentFrameNumber()：获取当前帧数
                {
                   backgroundMovie->stop();
                  pet_appearance->setPixmap(QPixmap(":/resources/static/default.png").scaled(pet_appearance->size()));
                }
                });
                pet_appearance->setMovie(backgroundMovie);
                backgroundMovie->start();

     // pet_appearance->setPixmap(QPixmap(":/resources/dynamic/9f99e657-57ba-4668-aad9-bb921eefc4a8.gif").scaled(pet_appearance->size()));
            }
    }
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
  {
      if (event->button() == Qt::LeftButton) {
          m_dragging = false;
          QMovie *backgroundMovie=new QMovie(this);

          backgroundMovie = new QMovie(":/resources/dynamic/9f99e657-57ba-4668-aad9-bb921eefc4a8.gif",QByteArray(),this);
          backgroundMovie->setScaledSize(pet_appearance->size());
          connect(backgroundMovie, &QMovie::frameChanged, [=](int frameNumber){
          if(frameNumber== backgroundMovie->frameCount() -1 )//currentFrameNumber()：获取当前帧数
          {
             backgroundMovie->stop();
             pet_appearance->setPixmap(QPixmap(":/resources/static/default.png").scaled(pet_appearance->size()));
          }
          });
          pet_appearance->setMovie(backgroundMovie);
          backgroundMovie->start();

         // pet_appearance->setPixmap(QPixmap(":/resources/static/default.png").scaled(pet_appearance->size()));
      }
  }
