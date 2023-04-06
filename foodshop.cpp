#include "foodshop.h"
#include "ui_foodshop.h"

foodShop::foodShop(QVector<Food> owned_pet_food,QWidget *parent) :
    QDialog(parent),owned_pet_food_(owned_pet_food),
    ui(new Ui::foodShop)


{
    ui->setupUi(this);

setWindowTitle("  可爱商店喵~   ");

// 初始化商品列表和价格和描述

   m_products.resize(3);
   m_products[0]={0,":/resources/static/fish.png","fish",35,99,-20};
   m_products[1]={1,":/resources/static/meat.png","meat",20,99,-10};
   m_products[2]={2,":/resources/static/vegetable.png","vegetable",12,99,-5};
   m_productList = new QListWidget(this);
for (int it=0; it < m_products.size(); ++it)
{
    m_productList->addItem(m_products[it].food_name);
}
connect(m_productList, &QListWidget::currentRowChanged, [=](int row)
{
    m_selectedProductId=row;
    m_productNameLabel->setText(m_products[ m_selectedProductId].food_name);
    m_productDescLabel->setText("它可以降低"+QString::number(m_products[m_selectedProductId].m_hunger)+"的饥饿度喵");
    m_productPriceLabel->setText(QString("价格 %1").arg(m_products[ m_selectedProductId].food_price));
});

   // 创建商品名称、描述和价格标签
   m_productNameLabel = new QLabel(this);
   m_productDescLabel = new QLabel(this);
   m_productPriceLabel = new QLabel(this);

   // 创建余额标签
   m_balance = 100;
   m_balanceLabel = new QLabel(QString("余额 %1").arg(100), this);

   //创建预览按钮
   m_viewButton=new QPushButton("预览商品信息",this);
   connect(m_viewButton,&QPushButton::clicked,this,&foodShop::viewProduct);
   // 创建购买按钮
   m_buyButton = new QPushButton("购买", this);
   connect(m_buyButton, &QPushButton::clicked, this, &foodShop::buyProduct);

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
void foodShop::viewProduct()
{

QPixmap pixmap=m_products[m_selectedProductId].food_picture;
QImage img=pixmap.toImage();
ImageDialog *dialog=new ImageDialog(img,this);
dialog->exec();

}

void foodShop::buyProduct()
{
double price = m_products[m_selectedProductId].food_price ;
if (m_balance >= price)
{
    m_balance -= price;
    m_balanceLabel->setText(QString("余额：%1").arg(m_balance));
    // 处理购买商品逻辑
    owned_pet_food_[m_selectedProductId].m_number++;
    QMessageBox::information(this, tr("购买成功"), tr("恭喜你购买成功了捏！"));
}

 else {
    // 余额不足，购买失败
    QMessageBox::warning(this, tr("购买失败"), tr("对不起，您的余额不足，请接着打工喵！"));
}
}



foodShop::~foodShop()
{
    delete ui;
}
