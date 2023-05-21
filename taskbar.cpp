#include "taskbar.h"
#include "ui_taskbar.h"

TaskBar::TaskBar(Task &task,int &point,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskBar),
    task_(task),
    point_(point)
{
    ui->setupUi(this);
    ui->label->setText(task.task_description);
    ui->progressBar->setValue(task.task_progress*100/task.task_target);
}

TaskBar::~TaskBar()
{
    delete ui;
}

void TaskBar::on_pushButton_clicked()
{
    if(task_.task_progress==task_.task_target&&!task_.task_finished)
    {
        point_+=task_.task_payment;
        task_.task_finished=true;
    }
}
