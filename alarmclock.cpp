#include "alarmclock.h"
#include "ui_alarmclock.h"
#include "mainwindow.h"

alarmclock::alarmclock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::alarmclock)
{
    ui->setupUi(this);
    connect(timer1,SIGNAL(timeout()),this,SLOT(checkFun()));//定时器timer每隔一段时间执行checkFun函数
}

alarmclock::~alarmclock()
{
    delete ui;
}

void alarmclock::getTime()//获取当前时间函数
{
    QTime t;
    int h=t.currentTime().hour();
    int min=t.currentTime().minute();
    int sec=t.currentTime().second();
    qDebug()<<"当前时间为:"<<h<<"时"<<min<<"分"<<sec<<"秒";
    ui->lineEdit->setText("当前时间为:"+t.currentTime().toString());//在消息框中显示当前时间
}

void alarmclock::on_timeEdit_editingFinished()//时间设置框函数
{
    tempTime=ui->timeEdit->time();//将时间设置框的时间赋值给tempTime
    qDebug()<<tempTime.toString();
    qDebug()<<"设置时间成功";
    this->ui->lineEdit->setText("设置闹钟时间为:"+tempTime.toString());//消息框显示设置时间
}

void alarmclock::on_pushButton_clicked()
{
    alarmclock::getTime();//一旦按下当前时间按钮则调用获取当前时间函数
}

void alarmclock::on_pushButton_4_clicked()
{
    timer1->start(1000);//设置间隔时间为一秒
    qDebug()<<timer1->isActive();//判断定时器是否在工作
    this->hide();
}

void alarmclock::checkFun()//检查当前时间是否和设置的时间相同
{
    qDebug()<<"更新";
    QTime t;
    if(tempTime.hour()==t.currentTime().hour()&&tempTime.minute()==t.currentTime().minute())
    {
        timer1->stop();//让定时器停止工作，因为只让闹钟执行一次
        this->show();
        ui->lineEdit->setText("设定时间已到！");
    }
}
