#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pet_hunger(80)
{    
    ui->setupUi(this);

    QString a= ":/resources/static/default.png";
    QString b= ":/resources/static/default2.png";

    point=new QVector<int>;
    point->push_back(100);
    owned_pet_appearances=new QVector<PetAppearance>;
    owned_pet_appearances->push_back(PetAppearance(2,a,"aa",20));
    owned_pet_appearances->push_back(PetAppearance(3,b,"BB",120));

    not_owned_pet_appearances=new QVector<PetAppearance>;
    not_owned_pet_appearances->push_back(PetAppearance(0,a,"a",10));
    not_owned_pet_appearances->push_back(PetAppearance(1,b,"B",10));

    owned_pet_food=new QVector<Food>;
    owned_pet_food->push_back(Food(0,":/resources/static/fish.png","fish",35,5,-20));
    owned_pet_food->push_back(Food(1,":/resources/static/meat.png","meat",20,5,-10));
    owned_pet_food->push_back(Food(2,":/resources/static/vegetable.png","vegetable",12,5,-5));
	
    pet_movements=new QVector<QString>;
    pet_movements->push_back(":/resources/movements/movement1.gif");
    pet_movements->push_back(":/resources/movements/movement2.gif");
    pet_movements->push_back(":/resources/movements/movement3.gif");
    pet_movements->push_back(":/resources/movements/hungry_movement.gif");
    hidetalkset=0;
    displayed_pet_appearance=(*owned_pet_appearances)[0];

    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);
    Qt::WindowFlags m_flags = windowFlags();
    setWindowFlags(m_flags|Qt::WindowStaysOnTopHint);

    pet_displayed_label=new QLabel(this);
    pet_displayed_label->resize(175,150);
    pet_displayed_label->move(125,50);

       screenedge_isattached_left = false;
       screenedge_isattached_right= false;
       screen_geometry = qApp->desktop()->availableGeometry(this);
       installEventFilter(this);
       m_petTalkLabel = new PushLabel(0,this);
       m_petTalkLabel->setWordWrap(true);
       m_petTalkLabel->setAlignment(Qt::AlignCenter);
       m_petTalkLabel->setStyleSheet("background-color: transparent; border: transparent; padding: 5px;font-size: 20px;");
       m_petTalkLabel->setGeometry(100, 0, 200, 60);
       m_petTalkLabel->hide();
       m_talkTimer = new QTimer(this);
       m_talkTimer->setInterval(10000);
       m_talkTimer->start();
       m_talkTimer2 = new QTimer(this);
       m_talkTimer2->setInterval(10000);
       connect(m_talkTimer2, &QTimer::timeout, this, &MainWindow::hiddenshowPetTalk);

    RefreshAppearance();
    showPetTalk();
    InitPetmovementMovies();
    InitHungerSystem();
    InitButton();
}
MainWindow::~MainWindow()
{
    delete ui;
    delete pet_displayed_label;
}

void MainWindow::OnEnterShopBtnClicked()
{
       QDialog *shopCenter=new QDialog(this);
       shopCenter->setWindowTitle("可爱商店喵~");
       enterappshop_btn=new QPushButton("装饰商店");
       connect(enterappshop_btn, &QPushButton::clicked, this, &MainWindow::OnEnterAppShopBtnClicked);
       enterfoodshop_btn=new  QPushButton("食物商店");
       connect(enterfoodshop_btn, &QPushButton::clicked, this, &MainWindow::OnEnterFoodShopBtnClicked);
       QVBoxLayout *layout=new QVBoxLayout(shopCenter);
       layout->addWidget(enterappshop_btn);
       layout->addWidget(enterfoodshop_btn);
       shopCenter->show();
}

void MainWindow::OnEnterAppShopBtnClicked()
{
    QDialog* dialog = qobject_cast<QDialog*>(sender()->parent());
    dialog->close();

    shopDress w(owned_pet_appearances,not_owned_pet_appearances,point);
    w.show();
    w.exec();
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == this && event->type() == QEvent::Move)
    {
        QPoint pos = this->pos();
        int width = this->width();
        int height = this->height();

        // 如果窗口在屏幕右侧，将其吸附到屏幕右侧并隐藏所有按钮,并停止计时
        if (pos.x() + width >= screen_geometry.width())
        {
            hidePetTalk();
            qDebug()<<"run";
            pet_displayed_label->setPixmap(QPixmap(":/resources/static/stopwall2.png").scaled(pet_displayed_label->size()));
            this->move(screen_geometry.width() - width+50, pos.y());
            screenedge_isattached_right = true;
            petwantplay_movie->stop();


        }
        else if (pos.x()-25 <= screen_geometry.x())
        {
            hidePetTalk();
            pet_displayed_label->setPixmap(QPixmap(":/resources/static/stopwall.png").scaled(pet_displayed_label->size()));
            this->move(screen_geometry.x()-175, pos.y());
            screenedge_isattached_left = true;
             petwantplay_movie->stop();

        }

        else if (screenedge_isattached_left||screenedge_isattached_right)
        {
            // 如果窗口不再靠在屏幕边缘，显示所有按钮，开始计时

        QMovie* backgroundMovie = new QMovie(this);
        backgroundMovie = new QMovie(":/resources/dynamic/mouse_dragging.gif", QByteArray(), this);
        backgroundMovie->setScaledSize(pet_displayed_label->size());
        pet_displayed_label->setMovie(backgroundMovie);
        backgroundMovie->start();
        screenedge_isattached_left = false;
        screenedge_isattached_right=false;
        appchoose_btn->show();
        feedpet_btn->show();
        entershop_btn->show();
        entergame_btn->show();
        m_talkTimer->start();
        petmovement_timer->start();
        pethunger_timer->start();
        }
    }

    // 将事件传递给基类处理
    return QMainWindow::eventFilter(watched, event);
}

// 实现hideAllButtons函数，用于隐藏所有窗口按钮

void MainWindow::OnEnterFoodShopBtnClicked()
{
    QDialog* dialog = qobject_cast<QDialog*>(sender()->parent());
    dialog->close();

    foodShop food(owned_pet_food,point);
    food.show();
    food.exec();
}
void MainWindow::OnEnterGameBtnClicked()
{
    if(pet_hunger>hungerlevel2)
    {
        QMessageBox::warning(this, "提示", "你没有足够的饥饿值进行游戏！", QMessageBox::Ok);
           return;
    }
    else{
     game*Game=new game(this);
     Game->show();
    }
}
void MainWindow::showPetTalk()
{



    // 在 QLabel 中设置一段话并显示出来
    m_petTalkLabel->setText("Hey, let's play a game!");
    m_petTalkLabel->show();
    petwantplay_movie = new QMovie(":/resources/motion/wantingplay.gif");
    petwantplay_movie->setScaledSize(pet_displayed_label->size());
    pet_displayed_label->setMovie(petwantplay_movie);
    petwantplay_movie->start();



    // 将 QLabel 转换为可单击的控件，并将其连接到一个槽函数
    m_petTalkLabel->setCursor(Qt::PointingHandCursor);
    connect(m_petTalkLabel, &PushLabel::clicked, this, &MainWindow::OnEnterGameBtnClicked);

    // 创建一个 QTimer，5 秒后调用 hidePetTalk() 槽函数
    QTimer::singleShot(5000, this, &MainWindow::hidePetTalk);

}

void MainWindow::hiddenshowPetTalk()
{

    m_petTalkLabel->setGeometry(0, 0, 200, 60);
    m_petTalkLabel->setText("Hey, let's play a game!");
    m_petTalkLabel->show();
if(screenedge_isattached_right)
{
//    if(hidetalkset==0)
    {
    hidetalkset=1;
    m_petTalkLabel->setCursor(Qt::PointingHandCursor);
    connect(m_petTalkLabel, &PushLabel::clicked, this, &MainWindow::OnEnterGameBtnClicked);
    QTimer::singleShot(5000, this, &MainWindow::hidePetTalk);
    }
}
if(screenedge_isattached_left){
    m_petTalkLabel->setGeometry(100, 0, 200, 60);
    m_petTalkLabel->setText("Hey, let's play a game!");
    m_petTalkLabel->show();
    if(hidetalkset==0)
    {
    m_petTalkLabel->setCursor(Qt::PointingHandCursor);
    connect(m_petTalkLabel, &PushLabel::clicked, this, &MainWindow::OnEnterGameBtnClicked);
    QTimer::singleShot(5000, this, &MainWindow::hidePetTalk);
    hidetalkset=1;
    }
}
}
void MainWindow::FeedPet()
{
    // Get the selected food item
    QListWidgetItem *selectedItem = ((QListWidget*)sender())->currentItem();

    // Get the text of the selected item
    QString foodType = selectedItem->text();

    // Reduce the hunger level based on the food type
    if (foodType == "Fish (" + QString::number((*owned_pet_food)[0].m_number) + ")")
    {
        if ((*owned_pet_food)[0].m_number < 1) {
            QMessageBox::warning(this, "提示", "你没有足够的鱼！", QMessageBox::Ok);
            return;
        }
        else
        {
        (*owned_pet_food)[0].m_number--;
        SetHunger((pet_hunger+(*owned_pet_food)[0].m_hunger));
        }

    }
    else if (foodType == "Meat (" + QString::number((*owned_pet_food)[1].m_number) + ")")
    {
        if ((*owned_pet_food)[1].m_number < 1)
        {
            QMessageBox::warning(this, "提示", "你没有足够的肉！", QMessageBox::Ok);
            return;
        }
        else
        {
            (*owned_pet_food)[1].m_number--;
            SetHunger((pet_hunger+(*owned_pet_food)[1].m_hunger));
        }
    }
    else if (foodType == "Vegetable (" + QString::number((*owned_pet_food)[2].m_number) + ")")
    {
        if ((*owned_pet_food)[2].m_number < 1) {
            QMessageBox::warning(this, "提示", "你没有足够的蔬菜！", QMessageBox::Ok);
            return;
        }
        else
        {
            (*owned_pet_food)[2].m_number--;
            SetHunger((pet_hunger+(*owned_pet_food)[2].m_hunger));
        }
    }
    pet_hunger = qMax(pet_hunger, 0);
    pet_displayed_label->setMovie(peteating_movie);
    peteating_movie->start();
    int totalTime = peteating_movie->frameCount() * peteating_movie->nextFrameDelay();
    QTimer::singleShot(2*totalTime, this, [=](){
        peteating_movie->stop();
        RefreshAppearance();
        petmovement_timer->start();
    });
}

int MainWindow::GetHunger() const
{
    return pet_hunger;
}

void MainWindow::SetHunger(int hunger)
{
    pet_hunger = hunger;
    pet_hunger = (hunger > 100) ? 100 : hunger;
    hunger_displayed_label->setText("Hunger level: " + QString::number(pet_hunger));
    emit HungerChanged(pet_hunger);

    if (pet_hunger == hungerlevel2)
    {
        emit HungerLevelCritical();
    }
}

void MainWindow::IncreaseHunger()
{
    SetHunger(pet_hunger + 1);
}

void MainWindow::enterEvent(QEvent *event)
{
    hunger_displayed_label->setText("Hunger level: " + QString::number(pet_hunger));
    hunger_displayed_label->show();
}

void MainWindow::leaveEvent(QEvent *event)
{
    hunger_displayed_label->hide();
}

void MainWindow::OnFeedPetBtnClicked()
{
    petmovement_timer->stop();
    QDialog *foodListDialog = new QDialog(this);
        foodListDialog->setWindowTitle("Select food");
        foodListDialog->resize(320, 80);

        // Create a list widget to show the food list
        QListWidget *foodListWidget = new QListWidget(foodListDialog);
        foodListWidget->setViewMode(QListView::IconMode);  // Set view mode to icon mode

        // Create a list item for each food
        QString fishText = "Fish (" + QString::number((*owned_pet_food)[0].m_number) + ")";
        QListWidgetItem *fishItem = new QListWidgetItem(QIcon(":/resources/static/fish.png"), fishText);
        fishItem->setSizeHint(QSize(80, 80));  // Set size hint for item
        foodListWidget->addItem(fishItem);

        QString meatText = "Meat (" + QString::number((*owned_pet_food)[1].m_number) + ")";
        QListWidgetItem *meatItem = new QListWidgetItem(QIcon(":/resources/static/meat.png"), meatText);
        meatItem->setSizeHint(QSize(80, 80));  // Set size hint for item
        foodListWidget->addItem(meatItem);

        QString veggieText = "Vegetable (" + QString::number((*owned_pet_food)[2].m_number) + ")";
        QListWidgetItem *veggieItem = new QListWidgetItem(QIcon(":/resources/static/vegetable.png"), veggieText);
        veggieItem->setSizeHint(QSize(80, 80));  // Set size hint for item
        foodListWidget->addItem(veggieItem);

        // Connect the item selection signal to the feedPet() slot
        connect(foodListWidget, SIGNAL(itemClicked(QListWidgetItem*)), foodListDialog, SLOT(accept()));

        connect(foodListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(FeedPet()));

        // Set the layout for the food list dialog
        QVBoxLayout *layout = new QVBoxLayout(foodListDialog);
        layout->addWidget(foodListWidget);
        foodListDialog->setLayout(layout);

        // Show the food list dialog
        foodListDialog->exec();
}

void MainWindow::InitPetmovementMovies()
{
    petmovement_timer=new QTimer(this);
    petmovement_timer->setInterval(12000);
    petmovement_timer->start();
    connect(petmovement_timer,&QTimer::timeout,[=]()
    {
        int move_index;
        if(pet_hunger<80) move_index=QRandomGenerator::global()->bounded(3);
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
                   RefreshAppearance();
                   delete displayed_movement;
               }
        });
        pet_displayed_label->setMovie(displayed_movement);
        displayed_movement->start();
    });
}

void MainWindow::InitHungerSystem()
{
    pethunger_timer = new QTimer(this);
    connect(pethunger_timer, SIGNAL(timeout()), this, SLOT(IncreaseHunger()));
    connect(this, SIGNAL(HungerLevelCritical()), this, SLOT(RefreshAppearance()));
    pethunger_timer->start(60000);

    peteating_movie = new QMovie(":/resources/motion/eating.gif");
    peteating_movie->setScaledSize(pet_displayed_label->size());

    hunger_displayed_label = new QLabel("Hunger level: " + QString::number(pet_hunger), this);
    hunger_displayed_label->hide();
    hunger_displayed_label->setGeometry(50, 50, 150, 30);
}

void MainWindow::InitButton()
{
    appchoose_btn = new QPushButton(this);
    appchoose_btn->setIcon(QIcon(":/resources/buttons/select_appearance.png"));
    appchoose_btn->move(1,1);
    appchoose_btn->resize(60,60);
    connect(appchoose_btn,&QPushButton::clicked,this,&MainWindow::OnAppChooseBtnClicked);

    feedpet_btn = new QPushButton("Feed pet", this);
    feedpet_btn->move(1,61);
    feedpet_btn->resize(60,60);
    connect(feedpet_btn,&QPushButton::clicked, this,&MainWindow::OnFeedPetBtnClicked);

    entershop_btn=new QPushButton("shop",this);
    entershop_btn->move(1,121);
    entershop_btn->resize(60,60);
    connect(entershop_btn,&QPushButton::clicked,this,&MainWindow::OnEnterShopBtnClicked);

    entergame_btn=new QPushButton("game",this);
    entergame_btn->move(1,181);
    entergame_btn->resize(60,60);
    connect(entergame_btn,&QPushButton::clicked,this,&MainWindow::OnEnterGameBtnClicked);
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
           m_talkTimer->stop();
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
        m_talkTimer->start();
        RefreshAppearance();
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
                    RefreshAppearance();
                }
            });
        pet_displayed_label->setMovie(backgroundMovie);
        backgroundMovie->start();
    }
}

void MainWindow::OnAppearanceChanged(int label_index)
{
    if(label_index!=-1) displayed_pet_appearance=(*owned_pet_appearances)[label_index];
    RefreshAppearance();
    petmovement_timer->start();
}

void MainWindow::OnAppChooseBtnClicked()
{
    petmovement_timer->stop();
    appchoose_win=new AppChooseWindow(owned_pet_appearances);
    connect(appchoose_win,&AppChooseWindow::AppearanceChanged,this,&MainWindow::OnAppearanceChanged);
    appchoose_win->show();
}

void MainWindow::RefreshAppearance()
{
    m_talkTimer2->stop();
    if(screenedge_isattached_left)
    {
        appchoose_btn->hide();
        feedpet_btn->hide();
        entershop_btn->hide();
        entergame_btn->hide();
        petmovement_timer->stop();
        pethunger_timer->stop();
        m_talkTimer->stop();
        pet_displayed_label->setPixmap(QPixmap(":/resources/static/stopwall.png").scaled(pet_displayed_label->size()));
        m_talkTimer2->start();
    }
    else if(screenedge_isattached_right)
    {
        appchoose_btn->hide();
        feedpet_btn->hide();
        entershop_btn->hide();
        entergame_btn->hide();
        petmovement_timer->stop();
        pethunger_timer->stop();
         m_talkTimer->stop();
        pet_displayed_label->setPixmap(QPixmap(":/resources/static/stopwall2.png").scaled(pet_displayed_label->size()));
        m_talkTimer2->start();
      }
    else if (pet_hunger>=hungerlevel2)
        {
            hidetalkset=0;
            pet_displayed_label->setPixmap(QPixmap(":/resources/static/default3.png").scaled(pet_displayed_label->size()));
        }
    else
        {
            hidetalkset=0;
        	pet_displayed_label->setPixmap(displayed_pet_appearance.app_picture.scaled(pet_displayed_label->size()));
            m_petTalkLabel->setGeometry(100, 0, 200, 60);
            connect(m_talkTimer, &QTimer::timeout, this, &MainWindow::showPetTalk);
             petwantplay_movie->start();
        }

}
void MainWindow::hidePetTalk()
{
    // 将 QLabel 隐藏，并取消与其的连接
    m_petTalkLabel->hide();
    m_petTalkLabel->disconnect();
    RefreshAppearance();
}
