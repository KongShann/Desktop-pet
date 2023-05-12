#include "taskwindow.h"
#include "ui_taskwindow.h"

TaskWindow::TaskWindow(QVector<Task> *tasklist,int &point,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskWindow)
{
    ui->setupUi(this);
    for(int i=0;i<tasklist->size();i++)
    {
        TaskBar* taskbar=new TaskBar((*tasklist)[i],point);
        QListWidgetItem* taskitem=new QListWidgetItem();
        taskitem->setSizeHint(taskbar->size());
        ui->listWidget->addItem(taskitem);
        ui->listWidget->setItemWidget(taskitem,taskbar);
    }
}

TaskWindow::~TaskWindow()
{
    delete ui;
}
