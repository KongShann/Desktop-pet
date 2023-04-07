#include "shopdress.h"
#include "mainwindow.h"
#include "petobjects_struct.h"
#include "ui_shopdress.h"

shopDress::shopDress(QVector<PetAppearance> *owned_pet_appearances,QVector<PetAppearance> *notowned_pet_appearances,QVector<int> *m_point,QWidget *parent) :
    QDialog(parent),notowned_pet_appearances_(notowned_pet_appearances),owned_pet_appearances_(owned_pet_appearances),m_balance(m_point),
    ui(new Ui::shopDress)
{
    ui->setupUi(this);

    setWindowTitle("   可爱商店喵~   ");

    // 初始化商品列表和价格和描述

    for(int i=0;i<notowned_pet_appearances_->size();i++)
    {
        m_products.push_back((*notowned_pet_appearances_)[i]);
    }
    // 创建商品列表控件

    m_productList = new QListWidget(this);
    for (int it=0; it < m_products.size(); ++it)
    {
        m_productList->addItem(m_products[it].app_name);
    }
    connect(m_productList, &QListWidget::currentRowChanged, [=](int row)
    {
        m_selectedProductId=row;
        m_productNameLabel->setText(m_products[ m_selectedProductId].app_name);
        m_productPriceLabel->setText(QString("价格 %1").arg(m_products[ m_selectedProductId].app_price));
    });

       // 创建商品名称、描述和价格标签
       m_productNameLabel = new QLabel(this);
       m_productDescLabel = new QLabel(this);
       m_productPriceLabel = new QLabel(this);

       // 创建余额标签

       m_balanceLabel = new QLabel(QString("余额 %1").arg((*m_balance)[0]), this);

       //创建预览按钮
       m_viewButton=new QPushButton("预览商品信息",this);
       connect(m_viewButton,&QPushButton::clicked,this,&shopDress::viewProduct);
       // 创建购买按钮
       m_buyButton = new QPushButton("购买", this);
       connect(m_buyButton, &QPushButton::clicked, this, &shopDress::buyProduct);

       // 创建布局
       QVBoxLayout *mainLayout = new QVBoxLayout(this);
       mainLayout->addWidget(m_productList);
       mainLayout->addWidget(m_productNameLabel);
       mainLayout->addWidget(m_productDescLabel);
       mainLayout->addWidget(m_productPriceLabel);
       mainLayout->addWidget(m_balanceLabel);
       mainLayout->addWidget(m_buyButton);
       mainLayout->addWidget(m_viewButton);
       setLayout(mainLayout);
}
class ImageDialog : public QDialog
{
public:
    ImageDialog(const QImage &img, QWidget *parent = nullptr)
        : QDialog(parent)
    {
        QLabel *imageLabel = new QLabel(this);
        imageLabel->setPixmap(QPixmap::fromImage(img));
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(imageLabel);
        setLayout(layout);
        setWindowTitle("主人快拿下我");
        setFixedSize(img.width(), img.height() + 30);
    }
};
void shopDress::viewProduct()
{

    QPixmap pixmap=m_products[m_selectedProductId].app_picture;
    QImage img=pixmap.toImage();
    ImageDialog *dialog=new ImageDialog(img,this);
    dialog->exec();

}

void shopDress::buyProduct()
{

    double price = m_products[m_selectedProductId].app_price ;
    if ((*m_balance)[0] >= price)
    {
        (*m_balance)[0] -= price;
        m_balanceLabel->setText(QString("余额：%1").arg((*m_balance)[0]));
        owned_pet_appearances_->push_back(m_products[m_selectedProductId]);
        notowned_pet_appearances_->erase(notowned_pet_appearances_->begin()+m_selectedProductId);
        // 处理购买商品逻辑
        QMessageBox::information(this, tr("购买成功"), tr("恭喜你购买成功了捏！"));
        this->close();
    }

     else {
        // 余额不足，购买失败
        QMessageBox::warning(this, tr("购买失败"), tr("对不起，您的余额不足，请接着打工喵！"));
    }
}


