#include "mainwindow.h"
#include "shopdress.h"
#include "ui_mainwindow.h"

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

    click_to_shopButton=new QPushButton("shop",this);

    connect(click_to_shopButton,&QPushButton::clicked,this,&MainWindow::gotoshop);


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
void MainWindow::gotoshop()
{
    shopDress shop;
    shop.show();
    shop.exec();
}

