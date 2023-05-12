#include "mainwindow.h"
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

    InitSettings();
    InitTaskSys();
    InitObjects();
    InitHungerSystem();
    CleanSystem();
    InitDisplayedLabel();
    InitPetmovementMovies();
    InitButton();
    RefreshButtons();
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

void MainWindow::OnEnterDailyFunctionBtnClicked()
{
    QDialog *FunctionCenter=new QDialog(this);
    FunctionCenter->setWindowTitle("日常功能");
    enteralarmclock_btn=new  QPushButton("闹钟");
    QVBoxLayout *layout=new QVBoxLayout(FunctionCenter);
    entercalendar_btn=new  QPushButton("日历");
    layout->addWidget(enteralarmclock_btn);
    layout->addWidget(entercalendar_btn);
    FunctionCenter->show();
    connect(enteralarmclock_btn, &QPushButton::clicked, this, &MainWindow::OnEnterAlarmClockBtnClicked);
    connect(entercalendar_btn, &QPushButton::clicked, this, &MainWindow::OnEnterCalendarBtnClicked);
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
        m_talkTimer->start();
        petmovement_timer->start();
        if(s_state_of_feedsys) pethunger_timer->start();
        dirty_timer->start();
        }
    }

    // 将事件传递给基类处理
    return QMainWindow::eventFilter(watched, event);
}


void MainWindow::OnEnterFoodShopBtnClicked()
{
    QDialog* dialog = qobject_cast<QDialog*>(sender()->parent());
    dialog->close();

    foodShop food(owned_pet_food,point);
    food.show();
    food.exec();
}

void MainWindow::OnEnterAlarmClockBtnClicked()
{
    QDialog* dialog = qobject_cast<QDialog*>(sender()->parent());
    dialog->close();

    myclock=new alarmclock();
    myclock->show();
}

void MainWindow::OnEnterCalendarBtnClicked(){
    m_calendarWidget = new CalendarWidget(this);
    m_calendarWidget->show();
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
     if((*tasklist)[2].task_target>(*tasklist)[0].task_progress)
     {
         (*tasklist)[2].task_progress++;
     }
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

//    qDebug()<<"aa";

    // 将 QLabel 转换为可单击的控件，并将其连接到一个槽函数
    m_petTalkLabel->setCursor(Qt::PointingHandCursor);
    connect(m_petTalkLabel, &PushLabel::clicked, this, &MainWindow::OnEnterGameBtnClicked);

    // 创建一个 QTimer，5 秒后调用 hidePetTalk() 槽函数
    QTimer::singleShot(5000, this, &MainWindow::hidePetTalk);

}

void MainWindow::hiddenshowPetTalk()
{


if(screenedge_isattached_right)
{

    m_petTalkLabel->setGeometry(0, 0, 200, 60);
    m_petTalkLabel->setText("Hey, let's play a game!");
    m_petTalkLabel->show();
    m_petTalkLabel->setCursor(Qt::PointingHandCursor);
    connect(m_petTalkLabel, &PushLabel::clicked, this, &MainWindow::OnEnterGameBtnClicked);
    QTimer::singleShot(5000, this, &MainWindow::hidePetTalk);

}
if(screenedge_isattached_left){
    m_petTalkLabel->setGeometry(100, 0, 200, 60);
    m_petTalkLabel->setText("Hey, let's play a game!");
    m_petTalkLabel->show();   
    m_petTalkLabel->setCursor(Qt::PointingHandCursor);
    connect(m_petTalkLabel, &PushLabel::clicked, this, &MainWindow::OnEnterGameBtnClicked);
    QTimer::singleShot(5000, this, &MainWindow::hidePetTalk); 
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
    if((*tasklist)[0].task_target>(*tasklist)[0].task_progress)
    {
        (*tasklist)[0].task_progress++;
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
    if(s_state_of_feedsys)
    {
        hunger_displayed_label->setText("Hunger level: " + QString::number(pet_hunger));
        hunger_displayed_label->show();
    }
}

void MainWindow::leaveEvent(QEvent *event)
{
    if(s_state_of_feedsys)
    {
        hunger_displayed_label->hide();
    }
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

void MainWindow::InitSettings()
{
    qRegisterMetaTypeStreamOperators<QVector<int>>("QVector<int>");
    qRegisterMetaTypeStreamOperators<QVector<bool>>("QVector<bool>");
    QString settings_filepath = QCoreApplication::applicationDirPath()+"/UserSettings.ini";
    user_settings=new QSettings(settings_filepath,QSettings::IniFormat);
    if(!QFile::exists(settings_filepath))
    {
        user_settings->setValue("Settings/feedsys",1);
        user_settings->setValue("Settings/tasksys",1);
        user_settings->setValue("Label/position",QPoint(125,50));
        user_settings->setValue("Pet/appearance",0);
        user_settings->setValue("Pet/hunger",20);
        user_settings->setValue("Pet/clean",100);
        user_settings->setValue("Pet/point",100);
        user_settings->setValue("Pet/owned_appearances",QVariant::fromValue(QVector<int>{0}));
        user_settings->setValue("Pet/not_owned_appearances",QVariant::fromValue(QVector<int>{1,2,3,4}));
        user_settings->setValue("Pet/owned_food",QVariant::fromValue(QVector<int>{1,1,1}));
        user_settings->setValue("Task/progress",QVariant::fromValue(QVector<int>{0,0,0,0}));
        user_settings->setValue("Task/finished",QVariant::fromValue(QVector<bool>{0,0,0,0}));
        user_settings->setValue("Settings/frequency",10000);
    }
    state_of_feedsys=user_settings->value("Settings/feedsys").toBool();
    state_of_tasksys=user_settings->value("Settings/tasksys").toBool();
    s_state_of_feedsys=state_of_feedsys;
    s_state_of_tasksys=state_of_tasksys;
    frequency_of_interact=user_settings->value("Settings/frequency").toInt();
}

void MainWindow::InitTaskSys()
{
    tasklist=new QVector<Task>;
    tasklist->push_back(Task(0,100,10,0,"喂食宠物10次",0));
    tasklist->push_back(Task(1,100,10,0,"清洁宠物10次",0));
    tasklist->push_back(Task(2,100,10,0,"与宠物游戏10次",0));
    tasklist->push_back(Task(3,100,3,0,"购买3件外观",0));
    progress_of_tasks=user_settings->value("Task/progress").value<QVector<int>>();
    if_finished_tasks=user_settings->value("Task/finished").value<QVector<bool>>();
    for(int i=0;i<tasklist->size();i++)
    {
        (*tasklist)[i].task_progress=progress_of_tasks[i];
        (*tasklist)[i].task_finished=if_finished_tasks[i];
    }
}

void MainWindow::InitObjects()
{
    point=user_settings->value("Pet/point").toInt();

    pet_appearances = new QVector<PetAppearance>;
    pet_appearances->push_back(PetAppearance(0,":/resources/static/default.png","wink",20));
    pet_appearances->push_back(PetAppearance(1,":/resources/static/default2.png","noface",20));
    pet_appearances->push_back(PetAppearance(2,":/resources/static/baseball.png","baseball",20));
    pet_appearances->push_back(PetAppearance(3,":/resources/static/shy.png","shy1",20));
    pet_appearances->push_back(PetAppearance(4,":/resources/static/shy2.png","shy2",20));

    owned_pet_appearances = new QVector<PetAppearance>;
    id_owned_apps=user_settings->value("Pet/owned_appearances").value<QVector<int>>();
    for(int i:id_owned_apps)
    {
        owned_pet_appearances->push_back((*pet_appearances)[i]);
    }
    not_owned_pet_appearances=new QVector<PetAppearance>;
    id_not_owned_apps=user_settings->value("Pet/not_owned_appearances").value<QVector<int>>();
    for(int i:id_not_owned_apps)
    {
        not_owned_pet_appearances->push_back((*pet_appearances)[i]);
    }

    owned_pet_food=new QVector<Food>;
    owned_pet_food->push_back(Food(0,":/resources/static/fish.png","fish",35,0,-20));
    owned_pet_food->push_back(Food(1,":/resources/static/meat.png","meat",20,0,-10));
    owned_pet_food->push_back(Food(2,":/resources/static/vegetable.png","vegetable",12,0,-5));
    num_owned_food=user_settings->value("Pet/owned_food").value<QVector<int>>();
    for(int i=0;i<owned_pet_food->size();i++)
    {
        (*owned_pet_food)[i].m_number=num_owned_food[i];
    }
}
void MainWindow::InitDisplayedLabel()
{
    pet_displayed_label=new QLabel(this);
    pet_displayed_label->resize(175,150);
    pet_displayed_label->move(125,50);
    window_position=user_settings->value("Label/position").toPoint();
    this->move(window_position);
    displayed_pet_appearance=(*owned_pet_appearances)[user_settings->value("Pet/appearance").toInt()];
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
    m_talkTimer->setInterval(15000);
    connect(m_talkTimer, &QTimer::timeout, this, &MainWindow::showPetTalk);
    m_talkTimer->start();
    m_talkTimer2 = new QTimer(this);
    m_talkTimer2->setInterval(frequency_of_interact*4);
    connect(m_talkTimer2, &QTimer::timeout, this, &MainWindow::hiddenshowPetTalk);
    showPetTalk();
    RefreshAppearance();
}

void MainWindow::InitPetmovementMovies()
{
    pet_movements=new QVector<QString>;
    pet_movements->push_back(":/resources/movements/movement1.gif");
    pet_movements->push_back(":/resources/movements/movement2.gif");
    pet_movements->push_back(":/resources/movements/movement3.gif");
    pet_movements->push_back(":/resources/movements/hungry_movement.gif");

    petmovement_timer=new QTimer(this);
    petmovement_timer->setInterval(frequency_of_interact);
    petmovement_timer->start();
    connect(petmovement_timer,&QTimer::timeout,[=]()
    {
        int move_index;
        if(pet_hunger<hungerlevel1) move_index=QRandomGenerator::global()->bounded(3);
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
    if(s_state_of_feedsys)
    {
        pet_hunger=user_settings->value("Pet/hunger").toInt();
        pethunger_timer = new QTimer(this);
        connect(pethunger_timer, SIGNAL(timeout()), this, SLOT(IncreaseHunger()));
    	connect(this, SIGNAL(HungerLevelCritical()), this, SLOT(RefreshAppearance()));
        pethunger_timer->start(60000);

        peteating_movie = new QMovie(":/resources/motion/eating.gif");
        peteating_movie->setScaledSize(QSize(175,150));

        hunger_displayed_label = new QLabel("Hunger level: " + QString::number(pet_hunger), this);
        hunger_displayed_label->hide();
        hunger_displayed_label->setGeometry(150, 50, 150, 30);
    }
    else
    {
        pet_hunger=0;
    }
}

void MainWindow::InitButton()
{
    show_buttons=false;

    appchoose_btn = new QPushButton(this);
    appchoose_btn->setIcon(QIcon(":/resources/buttons/select_appearance.png"));
    appchoose_btn->move(1,1);
    appchoose_btn->resize(45,45);
    connect(appchoose_btn,&QPushButton::clicked,this,&MainWindow::OnAppChooseBtnClicked);

    feedpet_btn = new QPushButton(this);
    feedpet_btn->setIcon(QIcon(":/resources/buttons/婴儿餐具.png"));
    feedpet_btn->move(1,46);
    feedpet_btn->resize(45,45);
    connect(feedpet_btn,&QPushButton::clicked, this,&MainWindow::OnFeedPetBtnClicked);

    entershop_btn=new QPushButton(this);
    entershop_btn->setIcon(QIcon(":/resources/buttons/alipay.png"));
    entershop_btn->move(1,91);
    entershop_btn->resize(45,45);
    connect(entershop_btn,&QPushButton::clicked,this,&MainWindow::OnEnterShopBtnClicked);

    exit_btn=new QPushButton(this);
    exit_btn->setIcon(QIcon(":/resources/buttons/x.png"));
    exit_btn->move(1,136);
    exit_btn->resize(45,45);
    connect(exit_btn,&QPushButton::clicked,this,&MainWindow::OnExitBtnClicked);

    entersettingswin_btn=new QPushButton(this);
    entersettingswin_btn->setIcon(QIcon(":/resources/buttons/设置.png"));
    entersettingswin_btn->move(46,1);
    entersettingswin_btn->resize(45,45);
    connect(entersettingswin_btn,&QPushButton::clicked,this,&MainWindow::OnEnterSettingsWindowBtnClicked);

    entertaskwin_btn=new QPushButton(this);
    entertaskwin_btn->setIcon(QIcon(":/resources/buttons/calendar-check.png"));
    entertaskwin_btn->move(46,46);
    entertaskwin_btn->resize(45,45);
    connect(entertaskwin_btn,&QPushButton::clicked,this,&MainWindow::OnEnterTaskWindowBtnClicked);
	
    entergame_btn=new QPushButton(this);
    entergame_btn->setIcon(QIcon(":/resources/buttons/玩具.png"));
    entergame_btn->move(46,91);
    entergame_btn->resize(45,45);
    connect(entergame_btn,&QPushButton::clicked,this,&MainWindow::OnEnterGameBtnClicked);

    wash_btn=new QPushButton(this);
    wash_btn->setIcon(QIcon(":/resources/buttons/浴缸.png"));
    wash_btn->move(46,136);
    wash_btn->resize(45,45);
    connect(wash_btn,&QPushButton::clicked,this,&MainWindow::OnCleanButtonClicked);
	
    enterdailyfunc_btn=new QPushButton(this);
    enterdailyfunc_btn->setIcon(QIcon(":/resources/buttons/控制日志.png"));
    enterdailyfunc_btn->move(46,181);
    enterdailyfunc_btn->resize(45,45);
    connect(enterdailyfunc_btn,&QPushButton::clicked,this,&MainWindow::OnEnterDailyFunctionBtnClicked);
}

void MainWindow::RefreshButtons()
{
    if(!show_buttons)
    {
        appchoose_btn->hide();
        feedpet_btn->hide();
        entershop_btn->hide();
        entergame_btn->hide();
        wash_btn->hide();
        exit_btn->hide();
        entertaskwin_btn->hide();
        entersettingswin_btn->hide();
		enterdailyfunc_btn->hide();
    }
    else
    {
        appchoose_btn->show();
        feedpet_btn->show();
        entershop_btn->show();
        entergame_btn->show();
        wash_btn->show();
        exit_btn->show();
        entertaskwin_btn->show();
        entersettingswin_btn->show();
		enterdailyfunc_btn->show();
    }

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    petmovement_timer->stop();
    if (event->button() == Qt::LeftButton) //检测到左键按压
    {
        petlabel_dragstartposition = event->pos(); //记录鼠标位置
        petlabel_isdragging = false;   //设置拖拽状态为否
    }
    if (event->button() == Qt::RightButton) //检测到右键按压
    {
        show_buttons=!show_buttons;
        RefreshButtons();
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

void MainWindow::OnExitBtnClicked()
{
    for(PetAppearance p:*owned_pet_appearances)
    {
        if(id_owned_apps.indexOf(p.app_id)==-1) id_owned_apps.push_back(p.app_id);
    }
    id_not_owned_apps.clear();
    for(PetAppearance p:*pet_appearances)
    {
        if(id_owned_apps.indexOf(p.app_id)==-1) id_not_owned_apps.push_back(p.app_id);
    }
    user_settings->setValue("Pet/owned_appearances",QVariant::fromValue(id_owned_apps));
    user_settings->setValue("Pet/not_owned_appearances",QVariant::fromValue(id_not_owned_apps));

    for(Food p:*owned_pet_food)
    {
        num_owned_food[p.food_id]=p.m_number;
    }
    user_settings->setValue("Pet/owned_food",QVariant::fromValue(num_owned_food));

    for(Task t:*tasklist)
    {
        progress_of_tasks[t.task_id]=t.task_progress;
        if_finished_tasks[t.task_id]=t.task_finished;
    }
    user_settings->setValue("Task/progress",QVariant::fromValue(progress_of_tasks));
    user_settings->setValue("Task/finished",QVariant::fromValue(if_finished_tasks));

    if(s_state_of_feedsys)
    {
        user_settings->setValue("Pet/hunger",pet_hunger);
    }

    user_settings->setValue("Pet/clean",cleanvalue);

    window_position=this->pos();
    user_settings->setValue("Label/position",window_position);
    user_settings->setValue("Pet/appearance",(*owned_pet_appearances).indexOf(displayed_pet_appearance));
    user_settings->setValue("Settings/feedsys",state_of_feedsys);
    user_settings->setValue("Settings/tasksys",state_of_tasksys);
    user_settings->setValue("Pet/point",point);
    user_settings->setValue("Settings/frequency",frequency_of_interact);
    user_settings->sync();
    qApp->exit(0);
}

void MainWindow::OnEnterSettingsWindowBtnClicked()
{
    settings_win=new SettingsWindow(state_of_feedsys,state_of_tasksys,frequency_of_interact);
    settings_win->show();
}

void MainWindow::OnEnterTaskWindowBtnClicked()
{
    if((*tasklist)[3].task_target>(*tasklist)[3].task_progress)
    {
        if(owned_pet_appearances->size()-1>(*tasklist)[3].task_target)
        {
             (*tasklist)[3].task_progress=(*tasklist)[3].task_target;
        }
        else
        {
             (*tasklist)[3].task_progress=owned_pet_appearances->size()-1;
        }
    }
    task_win=new TaskWindow(tasklist,point);
    task_win->show();
}

void MainWindow::RefreshAppearance()
{
    m_talkTimer2->stop();
    if(screenedge_isattached_left)
    {
        show_buttons=false;
        RefreshButtons();
        petmovement_timer->stop();
        if(s_state_of_feedsys) pethunger_timer->stop();
        m_talkTimer->stop();
        dirty_timer->stop();
        pet_displayed_label->setPixmap(QPixmap(":/resources/static/stopwall.png").scaled(pet_displayed_label->size()));
        m_talkTimer2->start();

    }
    else if(screenedge_isattached_right)
    {
        show_buttons=false;
        RefreshButtons();
        dirty_timer->stop();
        petmovement_timer->stop();
        if(s_state_of_feedsys) pethunger_timer->stop();
        m_talkTimer->stop();
        pet_displayed_label->setPixmap(QPixmap(":/resources/static/stopwall2.png").scaled(pet_displayed_label->size()));

        m_talkTimer2->start();
     }
    else if (pet_hunger>=hungerlevel2)
     {

            pet_displayed_label->setPixmap(QPixmap(":/resources/static/default3.png").scaled(pet_displayed_label->size()));
     }

    else if(cleanvalue < 50 && pet_hunger < hungerlevel2) // 当洁净值低于50且当前外观为干净时，改变外观
    {

            pet_displayed_label->setPixmap(QPixmap(":/resources/movements/dirty_movemoent.png").scaled(pet_displayed_label->size()));
    }
    else
        {

            pet_displayed_label->setPixmap(displayed_pet_appearance.app_picture.scaled(pet_displayed_label->size()));
            m_petTalkLabel->setGeometry(100, 0, 200, 60);
            m_talkTimer->start();
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

void MainWindow::CleanSystem()
{
    cleanvalue = user_settings->value("Pet/clean").toInt();
    dirty_timer = new QTimer(this);
    connect(dirty_timer, SIGNAL(timeout()), this, SLOT(DecreaseClean()));
    dirty_timer->start(60000); // 设置定时器，每10秒钟洁净值下降1点
}

void MainWindow::DecreaseClean()
{
    cleanvalue--; // 洁净值每次下降1点
    if (cleanvalue < 0) {
        cleanvalue = 0;
    }
    if(cleanvalue==49)
    {
        RefreshAppearance();
    }
}

void MainWindow::OnCleanButtonClicked()
{

    petmovement_timer->stop();
    m_talkTimer->stop();
    dirty_timer->stop();
    if(s_state_of_feedsys) pethunger_timer->stop();

    petwashing_movie = new QMovie(":/resources/motion/washing.gif");
    petwashing_movie->setScaledSize(pet_displayed_label->size());
    pet_displayed_label->setMovie(petwashing_movie);

    petwashing_movie->start();
    int totalTime = petwashing_movie->frameCount() * petwashing_movie->nextFrameDelay();
    QTimer::singleShot(totalTime, this, [=](){
    petwashing_movie->stop();
    RefreshAppearance();
    petmovement_timer->start();
    m_talkTimer->start();
    dirty_timer->start();
    if(s_state_of_feedsys) pethunger_timer->start();
    });
    cleanvalue += 10; // 点击按钮，洁净值增加10点

    if((*tasklist)[1].task_target>(*tasklist)[1].task_progress)
    {
        (*tasklist)[1].task_progress++;
    }

    if (cleanvalue > 100) {
        cleanvalue = 100; // 将洁净值限制在0到100之间
    }

}
