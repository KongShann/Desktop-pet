#include "mainwindow.h"
#include "shopdress.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
    , m_hunger(50)
{    
    ui->setupUi(this);

    QString a= ":/resources/static/default.png";
    QString b= ":/resources/static/default2.png";

    owned_pet_appearances=new QVector<PetAppearance>;
    owned_pet_appearances->push_back(PetAppearance(0,a));
    owned_pet_appearances->push_back(PetAppearance(1,b));

    displayed_pet_appearance=(*owned_pet_appearances)[1];

    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);
    Qt::WindowFlags m_flags = windowFlags();
    setWindowFlags(m_flags|Qt::WindowStaysOnTopHint);

    click_to_shopButton=new QPushButton("shop",this);
    connect(click_to_shopButton,&QPushButton::clicked,this,&MainWindow::gotoshop);

    pet_displayed_label=new QLabel(this);
    pet_displayed_label->resize(175,150);
    pet_displayed_label->move(125,50);
    pet_displayed_label->setPixmap(displayed_pet_appearance.app_picture.scaled(pet_displayed_label->size()));
    InitButton();

    m_hungerLabel = new QLabel("Hunger level: " + QString::number(m_hunger), this);
    m_hungerLabel->hide(); // Hide the label initially
    m_hungerLabel->setGeometry(50, 50, 150, 30);

    m_feedButton = new QPushButton("Feed pet", this);
    m_feedButton->setGeometry(50, 100, 100, 30);

    connect(m_feedButton, SIGNAL(clicked()), this, SLOT(showFoodList()));
    m_hungerTimer = new QTimer(this);
    connect(m_hungerTimer, SIGNAL(timeout()), this, SLOT(increaseHunger()));
    m_hungerTimer->start(1800000); // Increase hunger every second
    m_eatingMovie = new QMovie(":/resources/motion/eating.gif");
    m_eatingMovie->setScaledSize(pet_displayed_label->size());
    connect(m_eatingMovie, SIGNAL(finished()), this, SLOT(stopEating()));

    InitButton();
}
MainWindow::~MainWindow()
{
    delete ui;
    delete pet_displayed_label;
}
void MainWindow::gotoshop()
{
    shopDress shop;
    shop.show();
    shop.exec();
}
void MainWindow::feedPet()
{
    // Get the selected food item
       QListWidgetItem *selectedItem = ((QListWidget*)sender())->currentItem();

       // Get the text of the selected item
       QString foodType = selectedItem->text();

       // Reduce the hunger level based on the food type
       if (foodType == "Fish") {
           setHunger(m_hunger - 10);
       } else if (foodType == "Meat") {
           setHunger(m_hunger - 20);
       } else if (foodType == "Vegetables") {
           setHunger(m_hunger - 5);
       }
       m_hunger = qMax(m_hunger, 0);
       startEating();
}


int MainWindow::hunger() const
{
    return m_hunger;
}


void MainWindow::setHunger(int hunger)
{
    m_hunger = hunger;
    m_hungerLabel->setText("Hunger level: " + QString::number(m_hunger));
    emit hungerChanged(m_hunger);
}


void MainWindow::increaseHunger()
{
    setHunger(m_hunger + 1);
}


void MainWindow::enterEvent(QEnterEvent *event)
{
    m_hungerLabel->setText("Hunger level: " + QString::number(m_hunger));
    m_hungerLabel->show();
}

void MainWindow::leaveEvent(QEvent *event)
{
    m_hungerLabel->hide();
}



void MainWindow::showFoodList()
{
    QDialog *foodListDialog = new QDialog(this);
        foodListDialog->setWindowTitle("Select food");

        // Create a list widget to show the food list
        QListWidget *foodListWidget = new QListWidget(foodListDialog);
        foodListWidget->setViewMode(QListView::IconMode);  // Set view mode to icon mode

        // Create a list item for each food
        QListWidgetItem *fishItem = new QListWidgetItem(QIcon(":/resources/static/fish.png"), "Fish");
        fishItem->setSizeHint(QSize(96, 96));  // Set size hint for item
        foodListWidget->addItem(fishItem);

        QListWidgetItem *meatItem = new QListWidgetItem(QIcon(":/resources/static/meat.png"), "Meat");
        meatItem->setSizeHint(QSize(96, 96));  // Set size hint for item
        foodListWidget->addItem(meatItem);

        QListWidgetItem *veggieItem = new QListWidgetItem(QIcon(":/resources/static/vegetable.png"), "Vegetables");
        veggieItem->setSizeHint(QSize(96, 96));  // Set size hint for item
        foodListWidget->addItem(veggieItem);

        // Connect the item selection signal to the feedPet() slot
        connect(foodListWidget, SIGNAL(itemClicked(QListWidgetItem*)), foodListDialog, SLOT(accept()));
        connect(foodListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(feedPet()));

        // Set the layout for the food list dialog
        QVBoxLayout *layout = new QVBoxLayout(foodListDialog);
        layout->addWidget(foodListWidget);
        foodListDialog->setLayout(layout);

        // Show the food list dialog
        foodListDialog->exec();
}

void MainWindow::startEating()
{
pet_displayed_label->setMovie(m_eatingMovie);
m_eatingMovie->start();
int totalTime = m_eatingMovie->frameCount() * m_eatingMovie->nextFrameDelay();
    QTimer::singleShot(2*totalTime, this, SLOT(stopEating()));
}
void MainWindow::stopEating()
{
m_eatingMovie->stop();
pet_displayed_label->setPixmap(QPixmap(":/resources/static/default.png").scaled(pet_displayed_label->size()));
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
    displayed_pet_appearance=(*owned_pet_appearances)[label_index];
    pet_displayed_label->setPixmap(displayed_pet_appearance.app_picture.scaled(pet_displayed_label->size()));
}
void MainWindow::OnAppChooseBtnClicked(){
    appchoose_win=new AppChooseWindow(owned_pet_appearances);
    connect(appchoose_win,&AppChooseWindow::AppearanceChanged,this,&MainWindow::OnAppearanceChanged);
    appchoose_win->show();
}
