#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWindow(bool &state_of_feedsys,bool &state_of_tasksys,int &frequency_of_interact,QWidget *parent = nullptr);
    ~SettingsWindow();

private slots:
    void on_checkBox_stateChanged(int state);

    void on_checkBox_2_stateChanged(int state);

    void on_horizontalSlider_valueChanged(int value);

private:
    bool &state_of_feedsys_;
    bool &state_of_tasksys_;
    int &frequency_of_interact_;
    Ui::SettingsWindow *ui;
};

#endif // SETTINGSWINDOW_H
