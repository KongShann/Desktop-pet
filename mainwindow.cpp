#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdlib>
#include <ctime>
#include <QLabel>
#include <QMovie>

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
    if (event->button() == Qt::LeftButton) {
               m_dragging = true;
               m_startPos = event->globalPos() - frameGeometry().topLeft();
               QMovie *backgroundMovie=new QMovie(this);
               srand((int)time(0));
               int i=rand()%12;
               switch (i) {
               case 0:
                       backgroundMovie = new QMovie(":/resources/left_mouse_click/default3.gif",QByteArray(),this);
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
                   break;
               case 1:
                       backgroundMovie = new QMovie(":/resources/left_mouse_click/leftclick9.gif",QByteArray(),this);
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
                   break;
               case 2:
                       backgroundMovie = new QMovie(":/resources/left_mouse_click/leftclick16.gif",QByteArray(),this);
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
                   break;
               case 3:
                   backgroundMovie = new QMovie(":/resources/left_mouse_click/leftclick13.gif",QByteArray(),this);
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
                   break;
               case 4:
                   backgroundMovie = new QMovie(":/resources/left_mouse_click/leftclick14.gif",QByteArray(),this);
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
                   break;
               case 5:
                   backgroundMovie = new QMovie(":/resources/left_mouse_click/leftclick15.gif",QByteArray(),this);
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
                   break;
               case 6:
                   backgroundMovie = new QMovie(":/resources/left_mouse_click/leftclick6.gif",QByteArray(),this);
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
                   break;
               case 7:
                   backgroundMovie = new QMovie(":/resources/left_mouse_click/leftclick11.gif",QByteArray(),this);
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
                   break;
               case 8:
                   backgroundMovie = new QMovie(":/resources/left_mouse_click/leftclick8.gif",QByteArray(),this);
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
                   break;
               case 9:
                   backgroundMovie = new QMovie(":/resources/left_mouse_click/leftclick12.gif",QByteArray(),this);
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
                   break;
               case 10:
                   backgroundMovie = new QMovie(":/resources/left_mouse_click/leftclick17.gif",QByteArray(),this);
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
                   break;
               case 11:
                   backgroundMovie = new QMovie(":/resources/left_mouse_click/leftclick18.gif",QByteArray(),this);
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
                   break;
               }

           }
}
