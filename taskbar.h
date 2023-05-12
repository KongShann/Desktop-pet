#ifndef TASKBAR_H
#define TASKBAR_H

#include <QWidget>

#include "petobjects_struct.h"

namespace Ui {
class TaskBar;
}

class TaskBar : public QWidget
{
    Q_OBJECT

public:
    explicit TaskBar(Task &task,int &point,QWidget *parent = nullptr);
    ~TaskBar();

private slots:
    void on_pushButton_clicked();

private:
    Ui::TaskBar *ui;
    Task &task_;
    int &point_;
};

#endif // TASKBAR_H
