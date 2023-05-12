#include "calendarwidget.h"

void CalendarWidget::createReminder()
{
  // 获取用户选择的日期和输入的提醒内容
  QDate selectedDate = calendar ->selectedDate();
  QString reminderText = m_reminderInput->text();

  // 提醒用户
    if (reminderText.isEmpty()) {
            QMessageBox::warning(this, tr("提示"), tr("请输入提醒内容！"));
        } else {
            QMessageBox::information(this, tr("提醒"), tr("您已成功创建提醒：\n日期：%1\n内容：%2").arg(selectedDate.toString("yyyy-MM-dd")).arg(reminderText));
        }

    // 创建一个日程，并添加到列表中
    QPair<QDate, QString> reminder = qMakePair(selectedDate,reminderText);
    m_reminders.append(reminder);


    QTimer *timer = new QTimer(this);
    timer->setInterval(3600000); // 设置定时器间隔为1小时

    // 连接定时器的槽函数
    connect(timer, &QTimer::timeout, this, [=]() {
        // 获取当前时间和用户设置的提醒时间
        QDate currentTime = QDate::currentDate();
        QDate remindTime = selectedDate;

        // 比较时间，如果相同就弹出对话框提醒用户
        if (currentTime == remindTime) {
          //  QMessageBox::information(this, "Reminder", "It's time!");
          QMessageBox::information(this, "Reminder", QString("你创建的日程：%1 It's time!").arg(reminderText));
        }
    });
    // 启动定时器
     timer->start();
     // 将定时器添加到 m_timers 中
      m_timers.insert(m_reminders.size() - 1, timer);
 }

void CalendarWidget::viewReminder() {
    QDialog dialog;
    dialog.setWindowTitle("查看日程");

    QVBoxLayout *layout = new QVBoxLayout;
    QListWidget *listWidget = new QListWidget(&dialog);

    // 将所有日程添加到 QListWidget 中
    for (int i = 0; i < m_reminders.size(); i++) {
        QPair<QDate, QString> reminder = m_reminders.at(i);
        QString text = QString("%1 - %2").arg(reminder.first.toString("yyyy-MM-dd")).arg(reminder.second);
        QListWidgetItem *item = new QListWidgetItem(text);
        item->setData(Qt::UserRole, i);  // 设置该 item 的用户数据为日程在列表中的索引
        listWidget->addItem(item);
    }

   QPushButton *deleteButton = new QPushButton("删除选中日程", &dialog);
    connect(deleteButton, &QPushButton::clicked, [&]() {
        int index = listWidget->currentItem()->data(Qt::UserRole).toInt();  // 获取当前选中的日程在列表中的索引
        deleteReminder(index);  // 删除该日程
        // 停止并删除对应的定时器
              if (m_timers.contains(index)) {
                  QTimer *timer = m_timers.value(index);
                  timer->stop();
                  delete timer;
                  m_timers.remove(index);
              }
        listWidget->takeItem(listWidget->currentRow());  // 从 QListWidget 中删除该日程的 item
    });

    layout->addWidget(listWidget);
    layout->addWidget(deleteButton);
    dialog.setLayout(layout);
    dialog.exec();
}

void CalendarWidget::deleteReminder(int index) {

    // 停止并删除对应的定时器
       if (m_timers.contains(index)) {
           QTimer *timer = m_timers.value(index);
           timer->stop();
           delete timer;
           m_timers.remove(index);
       }
       m_reminders.removeAt(index);
}
