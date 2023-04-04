#ifndef APPCHOOSEWINDOW_H
#define APPCHOOSEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>

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
public slots:
    void OnPushLabelClicked(int label_index);
private slots:
    void on_confirm_button_clicked();

private:
    Ui::AppChooseWindow *ui;
    QGridLayout* gridlayout;
    QVector<PetAppearance>* owned_pet_apps;
    int label_index_;
signals:
    void AppearanceChanged(int label_index);
};

#endif // APPCHOOSEWINDOW_H
