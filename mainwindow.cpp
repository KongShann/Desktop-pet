#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_hunger(50)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);
    Qt::WindowFlags m_flags = windowFlags();
    setWindowFlags(m_flags|Qt::WindowStaysOnTopHint);
    pet_appearance=new QLabel(this);
    SelectAppearance();
    m_hungerLabel = new QLabel("Hunger level: " + QString::number(m_hunger), this);
       m_hungerLabel->hide(); // Hide the label initially
       m_hungerLabel->setGeometry(30, 30, 150, 30);
    m_feedButton = new QPushButton("Feed pet", this);
    m_feedButton->setGeometry(50, 100, 100, 30);
    connect(m_feedButton, SIGNAL(clicked()), this, SLOT(feedPet()));
    m_hungerTimer = new QTimer(this);
    connect(m_hungerTimer, SIGNAL(timeout()), this, SLOT(increaseHunger()));
    m_hungerTimer->start(1800000); // Increase hunger every second
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
void MainWindow::feedPet(){
    setHunger(m_hunger - 10);
        m_hunger = qMax(m_hunger, 0); // Make sure hunger is not negative
        m_hungerLabel->setText("Hunger level: " + QString::number(m_hunger));
}
int MainWindow::hunger() const
{
    return m_hunger;
}
void MainWindow::setHunger(int hunger)
{
    if (m_hunger != hunger) {
        m_hunger = hunger;
        emit hungerChanged(m_hunger);
    }
}
void MainWindow::increaseHunger()
{
    setHunger(m_hunger + 1);
}
void MainWindow::enterEvent(QEvent *event)
{
    m_hungerLabel->setText("Hunger level: " + QString::number(m_hunger));
    m_hungerLabel->show();
}

void MainWindow::leaveEvent(QEvent *event)
{
    m_hungerLabel->hide();
}

