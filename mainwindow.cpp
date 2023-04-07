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

    QString a= ":/resources/static/default.png";
    QString b= ":/resources/static/default2.png";

    owned_pet_appearances=new QVector<PetAppearance>;
    owned_pet_appearances->push_back(PetAppearance(0,a));
    owned_pet_appearances->push_back(PetAppearance(1,b));

    pet_movements=new QVector<QString>;
    pet_movements->push_back(":/resources/movements/movement1.gif");
    pet_movements->push_back(":/resources/movements/movement2.gif");
    pet_movements->push_back(":/resources/movements/movement3.gif");
    pet_movements->push_back(":/resources/movements/hungry_movement.gif");

    displayed_pet_appearance=(*owned_pet_appearances)[1];

    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);
    Qt::WindowFlags m_flags = windowFlags();
    setWindowFlags(m_flags|Qt::WindowStaysOnTopHint);

    pet_displayed_label=new QLabel(this);
    pet_displayed_label->resize(175,150);
    pet_displayed_label->move(125,50);
    pet_displayed_label->setPixmap(displayed_pet_appearance.app_picture.scaled(pet_displayed_label->size()));

    int pet_hungry=10;

    petmovement_timer=new QTimer(this);
    petmovement_timer->setInterval(6000);
    petmovement_timer->start();

    connect(petmovement_timer,&QTimer::timeout,[=]()
    {
        int move_index;
        if(pet_hungry<60) move_index=QRandomGenerator::global()->bounded(3);
        else move_index=QRandomGenerator::global()->bounded(pet_movements->size());
        QMovie *displayed_movement=new QMovie((*pet_movements)[move_index]);
        displayed_movement->setSpeed(50);
        displayed_movement->setCacheMode(QMovie::CacheAll);
        displayed_movement->setScaledSize(pet_displayed_label->size());
        QObject::connect(displayed_movement, &QMovie::frameChanged, [=](int frameNumber)
        {
               if (frameNumber == displayed_movement->frameCount() - 1)
               {
                   displayed_movement->stop();
                   pet_displayed_label->setPixmap(displayed_pet_appearance.app_picture.scaled(pet_displayed_label->size()));
                   delete displayed_movement;
               }
        });
        pet_displayed_label->setMovie(displayed_movement);
        displayed_movement->start();
    });

    InitButton();
}
MainWindow::~MainWindow()
{
    delete ui;
    delete pet_displayed_label;
}

void MainWindow::InitButton()
{
    appchoose_btn=new QPushButton(this);
    appchoose_btn->setIcon(QIcon(":/resources/buttons/select_appearance.png"));
    appchoose_btn->move(1,1);
    appchoose_btn->resize(60,60);
    connect(appchoose_btn,&QPushButton::clicked,this,&MainWindow::OnAppChooseBtnClicked);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    petmovement_timer->stop();
    if (event->button() == Qt::LeftButton) //检测到左键按压
    {
        petlabel_dragstartposition = event->pos(); //记录鼠标位置
        petlabel_isdragging = false;   //设置拖拽状态为否
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && !petlabel_isdragging) //左键按压移动还未进入拖动
    {
        QPoint dragDistance = event->globalPos() - petlabel_dragstartposition;
        if (dragDistance.manhattanLength()> QApplication::startDragDistance()) //判断是否进入拖动
        {
           petlabel_isdragging = true; //设置拖拽状态为是
           QPoint diff = event->globalPos() - petlabel_dragstartposition;
           move(diff);
           QMovie* backgroundMovie = new QMovie(this);
           backgroundMovie = new QMovie(":/resources/dynamic/mouse_dragging.gif", QByteArray(), this);
           backgroundMovie->setScaledSize(pet_displayed_label->size());
           pet_displayed_label->setMovie(backgroundMovie);
           backgroundMovie->start();
        }
    }
    else if((event->buttons() & Qt::LeftButton) && petlabel_isdragging) //已进入拖动且继续移动鼠标
    {
        QPoint diff = event->globalPos() - petlabel_dragstartposition;
        move(diff);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    petmovement_timer->start();
    if (event->button() == Qt::LeftButton && petlabel_isdragging) //左键释放结束拖动
    {
        petlabel_isdragging = false;
        pet_displayed_label->setPixmap(QPixmap(":/resources/static/default.png").scaled(pet_displayed_label->size()));
    }
    else if (event->button() == Qt::LeftButton && !petlabel_isdragging) //左键释放时还未进入拖动，判断为点击
    {
        QMovie* backgroundMovie = new QMovie(this);
        srand((int)time(0));
        int i = rand() % 12;
        QString pet_leftclick_movements[12] = {
                                                ":/resources/left_mouse_click/default3.gif",
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
                                                ":/resources/left_mouse_click/leftclick18.gif"
                                              };
        backgroundMovie = new QMovie(pet_leftclick_movements[i], QByteArray(), this);
        backgroundMovie->setScaledSize(pet_displayed_label->size());
        connect(backgroundMovie, &QMovie::frameChanged, [=](int frameNumber) {
            if (frameNumber == backgroundMovie->frameCount() - 1)//currentFrameNumber()：获取当前帧数
                {
                    backgroundMovie->stop();
                    pet_displayed_label->setPixmap(QPixmap(":/resources/static/default.png").scaled(pet_displayed_label->size()));
                }
            });
        pet_displayed_label->setMovie(backgroundMovie);
        backgroundMovie->start();
    }
}

void MainWindow::OnAppearanceChanged(int label_index)
{
    if(label_index!=-1) displayed_pet_appearance=(*owned_pet_appearances)[label_index];
    pet_displayed_label->setPixmap(displayed_pet_appearance.app_picture.scaled(pet_displayed_label->size()));
    petmovement_timer->start();
}

void MainWindow::OnAppChooseBtnClicked()
{
    petmovement_timer->stop();
    appchoose_win=new AppChooseWindow(owned_pet_appearances);
    connect(appchoose_win,&AppChooseWindow::AppearanceChanged,this,&MainWindow::OnAppearanceChanged);
    appchoose_win->show();
}
