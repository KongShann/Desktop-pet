#include "settingswindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(bool &state_of_feedsys,bool &state_of_tasksys,int &frequency_of_interact,QWidget *parent) :
    QWidget(parent),
    state_of_feedsys_(state_of_feedsys),
    state_of_tasksys_(state_of_tasksys),
    frequency_of_interact_(frequency_of_interact),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    ui->checkBox->setChecked(state_of_feedsys);
    ui->checkBox_2->setChecked(state_of_tasksys);
    if(ui->checkBox->checkState()!=Qt::Checked)
    {
        ui->checkBox_2->setDisabled(true);
    }
    ui->horizontalSlider->setValue(101-(frequency_of_interact/10000));
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::on_checkBox_stateChanged(int state)
{
    if(state==Qt::Checked)
    {
        state_of_feedsys_=true;
        ui->checkBox_2->setEnabled(true);
    }
    else
    {
        ui->checkBox_2->setChecked(false);
        state_of_feedsys_=false;
        ui->checkBox_2->setDisabled(true);
    }
}

void SettingsWindow::on_checkBox_2_stateChanged(int state)
{
    if(state==Qt::Checked)
    {
        state_of_tasksys_=true;
    }
    else
    {
        state_of_tasksys_=false;
    }
}

void SettingsWindow::on_horizontalSlider_valueChanged(int value)
{
    if(value==0)
    {
        frequency_of_interact_= 100000000;
    }
    else
    {
        frequency_of_interact_= (101-value)*10000;
    }
}
