#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QMovie>
#include <QRandomGenerator>

#include "petobjects_struct.h"
#include "appchoosewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void OnAppearanceChanged(int label_index);
    void OnAppChooseBtnClicked();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void InitButton();

private:
    Ui::MainWindow *ui;

    QVector<PetAppearance> *owned_pet_appearances;
    PetAppearance displayed_pet_appearance;
    QVector<QString> *pet_movements;

    QTimer* movement_timer;

    QLabel* pet_displayed_label; //外观显示Lable指针

    QPushButton* appchoose_btn; //切换外观按钮指针

    AppChooseWindow* appchoose_win; //切换外观窗口

signals:
};
#endif // MAINWINDOW_H
