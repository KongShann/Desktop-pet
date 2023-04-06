#ifndef SHOPDRESS_H
#define SHOPDRESS_H

#include <QDialog>
#include <QtWidgets>
#include <QListWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QMap>

#include "petobjects_struct.h"

namespace Ui {
class shopDress;
}

class shopDress : public QDialog
{
    Q_OBJECT


public:
    explicit shopDress(QWidget *parent = nullptr);
    void packlogic();
    ~shopDress();


private:
    void createProductList();
    void createProductDetail();
    QListWidget *m_productList;

    std::vector<PetAppearance> m_products;


    QLabel *m_productNameLabel;
    QLabel *m_productDescLabel;
    QLabel *m_productPriceLabel;
    QLabel *m_balanceLabel;
    QLabel *m_productIconLabel;
    QPushButton *m_buyButton;
    QPushButton *m_viewButton;

    std::vector<bool> have_bought;

    int m_selectedProductId;
    int m_balance;
    Ui::shopDress *ui;


private slots:
    void buyProduct();
    void viewProduct();


};


#endif // SHOPDRESS_H
