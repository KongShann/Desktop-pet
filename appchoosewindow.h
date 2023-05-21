#ifndef APPCHOOSEWINDOW_H
#define APPCHOOSEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <cmath>

#include "pushlabel.h"
#include "petobjects_struct.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AppChooseWindow; }
QT_END_NAMESPACE
class AppChooseWindow : public QWidget
{
    Q_OBJECT

public:
    AppChooseWindow(QVector<PetAppearance>* owned_pet_apps,QWidget *parent=nullptr);
    ~AppChooseWindow();  
private slots:
    void on_confirm_button_clicked();
    void OnPushLabelClicked(int label_index);
private:
    Ui::AppChooseWindow *ui;
    QGridLayout* gridlayout;
    QVector<PetAppearance>* owned_pet_apps;
    int label_index_;
signals:
    void AppearanceChanged(int label_index);
};

#endif // APPCHOOSEWINDOW_H
