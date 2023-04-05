#ifndef SHOPDRESS_H
#define SHOPDRESS_H

#include <QDialog>
#include <QtWidgets>
#include <QListWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QMap>


namespace Ui {
class shopDress;
}

class shopDress : public QDialog
{
    Q_OBJECT


public:
    explicit shopDress(QWidget *parent = nullptr);
    ~shopDress();

private:
    void createProductList();
    void createProductDetail();
    QListWidget *m_productList;
    QMap<int, QString> m_products; // 商品ID和名称的映射
    QMap<int, double> m_productPrices;// 商品ID和价格的映射
    QMap<int,QString>  m_productDesc;//商品ID和描述的映射
    QMap<int,QPixmap> m_productsIcons;

    QLabel *m_productNameLabel;
    QLabel *m_productDescLabel;
    QLabel *m_productPriceLabel;
    QLabel *m_balanceLabel;
    QLabel *m_productIconLabel;
    QPushButton *m_buyButton;
    QPushButton *m_viewButton;


    int m_selectedProductId;
    int m_balance;
    Ui::shopDress *ui;
private slots:
    void buyProduct();
    void viewProduct();
};


#endif // SHOPDRESS_H
