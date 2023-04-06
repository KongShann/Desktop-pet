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
    if (event->button() == Qt::LeftButton) {
               m_dragging = true;
               m_startPos = event->globalPos() - frameGeometry().topLeft();
               QMovie *backgroundMovie=new QMovie(this);
               srand((int)time(0));
               int i=rand()%12;
               QString gif[12]={":/resources/left_mouse_click/default3.gif",":/resources/left_mouse_click/leftclick9.gif",":/resources/left_mouse_click/leftclick16.gif",":/resources/left_mouse_click/leftclick13.gif",":/resources/left_mouse_click/leftclick14.gif",":/resources/left_mouse_click/leftclick15.gif",":/resources/left_mouse_click/leftclick6.gif",":/resources/left_mouse_click/leftclick11.gif",":/resources/left_mouse_click/leftclick8.gif",":/resources/left_mouse_click/leftclick12.gif",":/resources/left_mouse_click/leftclick17.gif",":/resources/left_mouse_click/leftclick18.gif"};
               backgroundMovie = new QMovie(gif[i],QByteArray(),this);
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

           }
}
