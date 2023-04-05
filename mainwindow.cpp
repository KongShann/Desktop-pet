#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    movement_timer=new QTimer(this);
    movement_timer->setInterval(3000);
    movement_timer->start();


    connect(movement_timer,&QTimer::timeout,[=](){
        int move_index;
        if(pet_hungry<60) move_index=QRandomGenerator::global()->bounded(3);
        else move_index=QRandomGenerator::global()->bounded(pet_movements->size());
        QMovie *displayed_movement=new QMovie((*pet_movements)[move_index]);
        displayed_movement->setSpeed(50);
        displayed_movement->setCacheMode(QMovie::CacheAll);
        displayed_movement->setScaledSize(pet_displayed_label->size());
        QObject::connect(displayed_movement, &QMovie::frameChanged, [=](int frameNumber){
               if (frameNumber == displayed_movement->frameCount() - 1) {
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

void MainWindow::InitButton(){
    appchoose_btn=new QPushButton(this);
    appchoose_btn->setIcon(QIcon(":/resources/buttons/select_appearance.png"));
    appchoose_btn->move(1,1);
    appchoose_btn->resize(60,60);
    connect(appchoose_btn,&QPushButton::clicked,this,&MainWindow::OnAppChooseBtnClicked);
}

void MainWindow::OnAppearanceChanged(int label_index)
{
    if(label_index!=-1) displayed_pet_appearance=(*owned_pet_appearances)[label_index];
    pet_displayed_label->setPixmap(displayed_pet_appearance.app_picture.scaled(pet_displayed_label->size()));
    movement_timer->start();
}
void MainWindow::OnAppChooseBtnClicked(){
    movement_timer->stop();
    appchoose_win=new AppChooseWindow(owned_pet_appearances);
    connect(appchoose_win,&AppChooseWindow::AppearanceChanged,this,&MainWindow::OnAppearanceChanged);
    appchoose_win->show();
}
