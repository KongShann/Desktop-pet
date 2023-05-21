#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QtWidgets>
#include <QCalendarWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

class CalendarWidget : public QWidget {

private slots:
    void createReminder();
    void viewReminder();
    void deleteReminder(int index);
public:
    QCalendarWidget *calendar;//日历窗口指针
    QLineEdit *m_reminderInput;
    QPushButton *m_createButton;
    QPushButton *m_viewButton;
    QWidget *widget;
    QHBoxLayout *hLayout;
    QVBoxLayout *layout;

private:
    QList<QPair<QDate, QString>> m_reminders;  // 保存所有日程的列表
    QMap<int, QTimer*> m_timers;
public:
    CalendarWidget(QWidget *parent = nullptr) : QWidget(parent) {
    widget = new QWidget;
    widget->setWindowTitle("Custom Calendar");
    // 创建一个QCalendarWidget对象作为日历
    calendar = new QCalendarWidget(widget);
    m_reminderInput = new QLineEdit(this);
    m_createButton = new QPushButton(tr("创建日程"), this);
    m_viewButton = new QPushButton(tr("查看日程"), this);
   // 创建一个横向的QHBoxLayout对象作为输入框和按钮的布局
    hLayout = new QHBoxLayout;
    hLayout->addWidget(m_reminderInput);
    hLayout->addWidget(m_createButton);
    hLayout->addWidget(m_viewButton);
   // 将输入框和按钮的布局添加到垂直布局中
    layout= new QVBoxLayout;
    layout->addWidget(calendar);
    layout->addLayout(hLayout);
    widget->setLayout(layout);
   // 连接按钮的点击信号和槽函数
    widget->show();
    connect(m_createButton, &QPushButton::clicked, this, &CalendarWidget::createReminder);
    connect(m_viewButton, &QPushButton::clicked, this, &CalendarWidget::viewReminder);
    }};
#endif // CALENDARWIDGET_H

