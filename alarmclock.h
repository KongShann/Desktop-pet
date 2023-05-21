#ifndef ALARMCLOCK_H
#define ALARMCLOCK_H

#include <QDialog>
#include <QWidget>
#include <QMediaPlayer>
#include <QTimeEdit>
#include <QTimer>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
QT_BEGIN_NAMESPACE
namespace Ui { class alarmclock; }
QT_END_NAMESPACE

class alarmclock : public QWidget
{
    Q_OBJECT

public:
    explicit alarmclock(QWidget *parent = nullptr);
    ~alarmclock();
    void getTime();//获取当前时间的函数

private slots:
    void on_pushButton_clicked();

    void on_timeEdit_editingFinished();

    void checkFun();//检查当前时间是否到达设置的时间，此函数必须放在private slots中

    void on_pushButton_4_clicked();

private:
    QTime tempTime;//临时时间，用于存放设置好的时间
    QTimer *timer1=new QTimer(this);//设置定时器
private:
    Ui::alarmclock *ui;
};

#endif // ALARMCLOCK_H

