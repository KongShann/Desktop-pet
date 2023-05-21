#include "appchoosewindow.h"
#include "ui_appchoosewindow.h"


AppChooseWindow::AppChooseWindow(QVector<PetAppearance>* owned_pet_apps,QWidget *parent)
    :QWidget(parent)
    ,ui(new Ui::AppChooseWindow)
    ,owned_pet_apps(owned_pet_apps)
    ,label_index_(-1)
{
    ui->setupUi(this);
    gridlayout=new QGridLayout(ui->scrollAreaWidgetContents);
    gridlayout->setColumnStretch(0, 1);
    gridlayout->setColumnStretch(1, 1);
    gridlayout->setColumnStretch(2, 1);
    int num_of_rows = ceil(owned_pet_apps->count() / 3.0);
    for (int row = 0; row < num_of_rows; ++row) {
        for (int col = 0; col < 3; ++col) {
            int index = row * 3 + col;
            if (index >=owned_pet_apps->count())
                break;
            PushLabel* app_label = new PushLabel(index);
            connect(app_label,&PushLabel::clicked,this,&AppChooseWindow::OnPushLabelClicked);
            app_label->setPixmap((*owned_pet_apps)[index].app_picture.scaled(ui->scrollAreaWidgetContents->width()/3,1000,Qt::KeepAspectRatio));
            gridlayout->addWidget(app_label, row, col, Qt::AlignTop|Qt::AlignLeft);
        }
    }
}

AppChooseWindow::~AppChooseWindow()
{
    delete ui;
}

void AppChooseWindow::OnPushLabelClicked(int label_index)
{
    ui->view_label->setPixmap((*owned_pet_apps)[label_index].app_picture.scaled(ui->view_label->size(),Qt::KeepAspectRatio));
    label_index_=label_index;
}

void AppChooseWindow::on_confirm_button_clicked()
{
    emit AppearanceChanged(label_index_);
    this->close();
}
