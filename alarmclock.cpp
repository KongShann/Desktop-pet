#include "alarmclock.h"
#include "ui_alarmclock.h"
#include "mainwindow.h"

alarmclock::alarmclock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::alarmclock)
{
    ui->setupUi(this);
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

void alarmclock::setMedia1()//设置播放器播放的路径为第一首
{
player.setVolume(30);
player.setMedia(QUrl::fromLocalFile("C:/mymusic/Fall Out Boy - The Phoenix.mp3"));//后面是播放音乐的文件路径
}

void alarmclock::setMedia2()//设置播放器播放的路径为第二首
{
player.setVolume(30);
player.setMedia(QUrl::fromLocalFile("C:/mymusic/The Cab - Lock Me Up.mp3"));
}

void alarmclock::setMedia3()//设置播放器播放的路径为第三首
{
player.setVolume(30);
player.setMedia(QUrl::fromLocalFile("C:/mymusic/Yoohsic Roomz - Eutopia.mp3"));
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

void alarmclock::on_pushButton_2_clicked()
{
    if(checkNum==1)//如果是选择的音乐1，则将播放器的地址选择为第一曲
        alarmclock::setMedia1();
        else if(checkNum==2)
        alarmclock::setMedia2();//如果是选择的音乐2，则将播放器的地址选择为第二曲
        else if(checkNum==3)
        alarmclock::setMedia3();//如果是选择的音乐3，则将播放器的地址选择为第三曲
        player.play();//播放器开始播放音乐
        qDebug()<<"开始播放";
        ui->lineEdit->setText("播放");//消息框显示播放
}

void alarmclock::on_pushButton_3_clicked()
{
    player.stop();
        qDebug()<<"暂停";
        ui->lineEdit->setText("暂停");
}

void alarmclock::on_radioButton_clicked()
{
    checkNum=1;//将选择播放哪首音乐的变量赋值为1
}

void alarmclock::on_radioButton_2_clicked()
{
    checkNum=2;//将选择播放哪首音乐的变量赋值为2
}

void alarmclock::on_radioButton_3_clicked()
{
    checkNum=3;//将选择播放哪首音乐的变量赋值为3
}

void alarmclock::on_pushButton_4_clicked()
{
    connect(timer1,SIGNAL(timeout()),this,SLOT(checkFun()));//定时器timer每隔一段时间执行checkFun函数
        timer1->start(1000);//设置间隔时间为一秒
        qDebug()<<timer1->isActive();//判断定时器是否在工作
}

void alarmclock::checkFun()//检查当前时间是否和设置的时间相同
{
qDebug()<<"更新";
QTime t;
if(tempTime.hour()==t.currentTime().hour()&&tempTime.minute()==t.currentTime().minute())
{
alarmclock::on_pushButton_2_clicked();//当时间相同时，开始执行播放函数，播放选择好的音乐
timer1->stop();//让定时器停止工作，因为只让闹钟执行一次
}
}
