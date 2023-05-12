#ifndef TASKWINDOW_H
#define TASKWINDOW_H

#include <QWidget>

#include "taskbar.h"
#include "petobjects_struct.h"

namespace Ui {
class TaskWindow;
}

class TaskWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TaskWindow(QVector<Task> *tasklist,int &point,QWidget *parent = nullptr);
    ~TaskWindow();

private:
    Ui::TaskWindow *ui;
};

#endif // TASKWINDOW_H
