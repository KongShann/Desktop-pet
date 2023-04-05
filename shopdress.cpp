#include "shopdress.h"
#include "ui_shopdress.h"

shopDress::shopDress(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::shopDress)
{
    ui->setupUi(this);
    setWindowTitle("  可爱商店喵~   ");

    // 初始化商品列表和价格和描述
    m_products.insert(0, "0");
    m_products.insert(1, "1");
    m_products.insert(2, "2");
    m_products.insert(3,"3");
    m_productPrices.insert(0, 5.0);
    m_productPrices.insert(1, 10.0);
    m_productPrices.insert(2, 15.0);
    m_productPrices.insert(3, 50.0);
    m_productDesc.insert(0,"精品");
    m_productDesc.insert(1,"黄金");
    m_productDesc.insert(2,"钻石");
    m_productDesc.insert(3, "RED");
    // 创建商品列表控件
    m_productList = new QListWidget(this);
    for (auto it = m_products.begin(); it != m_products.end(); ++it)
    {
        m_productList->addItem(it.value());
    }
    connect(m_productList, &QListWidget::currentRowChanged, [=](int row)
    {
        m_selectedProductId = row;
        m_productNameLabel->setText(m_products[m_selectedProductId]);
        m_productDescLabel->setText("这是" + m_productDesc[m_selectedProductId] + " 品质");
        m_productPriceLabel->setText(QString("价格：%1").arg(m_productPrices[m_selectedProductId]));
    });

       // 创建商品名称、描述和价格标签
       m_productNameLabel = new QLabel(this);
       m_productDescLabel = new QLabel(this);
       m_productPriceLabel = new QLabel(this);

       // 创建余额标签
       m_balance = 100;
       m_balanceLabel = new QLabel(QString("余额：%1").arg(m_balance), this);

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

    QImage img(":/"+m_products[m_selectedProductId]+".jpg");
    ImageDialog *dialog=new ImageDialog(img,this);
    dialog->exec();

}

void shopDress::buyProduct()
{
    double price = m_productPrices[m_selectedProductId] ;
    if (m_balance >= price)
    {
        m_balance -= price;
        m_balanceLabel->setText(QString("余额：%1").arg(m_balance));
        // 处理购买商品逻辑
         QMessageBox::information(this, tr("购买成功"), tr("恭喜你购买成功了捏！"));
    }

     else {
        // 余额不足，购买失败
        QMessageBox::warning(this, tr("购买失败"), tr("对不起，您的余额不足，请接着打工喵！"));
    }
}

shopDress::~shopDress()
{
    delete ui;
}

