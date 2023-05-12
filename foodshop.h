#ifndef FOODSHOP_H
#define FOODSHOP_H

#include <QDialog>
#include <QtWidgets>
#include <QListWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QMap>

#include "petobjects_struct.h"
namespace Ui {
class foodShop;
}

class foodShop : public QDialog
{
    Q_OBJECT

public:
    explicit foodShop(QVector<Food> *owned_pet_food,int &m_point,QWidget *parent = nullptr);

    ~foodShop();
private:
    void createProductList();
    void createProductDetail();
    QListWidget *m_productList;

    std::vector<Food> m_products;


    QLabel *m_productNameLabel;
    QLabel *m_productDescLabel;
    QLabel *m_productPriceLabel;
    QLabel *m_balanceLabel;
    QLabel *m_productIconLabel;
    QPushButton *m_buyButton;
    QPushButton *m_viewButton;

    QVector<Food> *owned_pet_food_;//数据成员
    int m_selectedProductId;
    int &m_balance;
    Ui::foodShop *ui;


private slots:
    void buyProduct();
    void viewProduct();


};
#endif // FOODSHOP_H
