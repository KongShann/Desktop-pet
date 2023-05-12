#include "game.h"
#include "ui_game.h"

using namespace std;
QString filename1 = ":/resources/game/rock.png";
QString filename2 = ":/resources/game/scissor.png";
QString filename3 = ":/resources/game/paper.png";
game::game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::game)
{
    ui->setupUi(this);
    QImage* img1=new QImage,*img2=new QImage,*img3=new QImage;
    img1->load(filename1);
    img2->load(filename2);
    img3->load(filename3);
    ui->label_5->setPixmap(QPixmap::fromImage(*img1));
    ui->label_5->setScaledContents(true);
    ui->label_6->setPixmap(QPixmap::fromImage(*img2));
    ui->label_6->setScaledContents(true);
    ui->label_7->setPixmap(QPixmap::fromImage(*img3));
    ui->label_7->setScaledContents(true);
    QMovie *readygif = new QMovie(":/resources/motion/readygif.gif");
    readygif->setScaledSize(QSize(100, 100));
    ui->label_2->setMovie(readygif);
    readygif->start();

}

 QString game::competition(QString man,QString computer)
{
    int manNum = 0;
    int computerNum = 0;
    QString qstrResult = "";
    if(man == filename1)
    {
        manNum = 0;
    }
    else if(man == filename2)
    {
        manNum = 1;
    }
    else
    {
        manNum = 2;
    }

    if(computer == filename1)
    {
        computerNum = 0;
    }
    else if(computer == filename2)
    {
        computerNum = 1;
    }
    else
    {
        computerNum = 2;
    }

    int result = (manNum - computerNum + 4) % 3 - 1;
    if(result < 0)
    {
        qstrResult = "你赢了！";
        QMovie *wingif = new QMovie(":/resources/motion/wingif.gif");
        wingif->setScaledSize(QSize(100, 100));
        ui->label_2->setMovie(wingif);
        wingif->start();
    }
    else if(result == 0)
    {
        QMovie *pinggif = new QMovie(":/resources/motion/ping.gif");
        pinggif->setScaledSize(QSize(100, 100));
        ui->label_2->setMovie(pinggif);
        pinggif->start();
        qstrResult = "平局。";
    }
    else
    {
        QMovie *losegif = new QMovie(":/resources/motion/lose.gif");
        losegif->setScaledSize(QSize(100, 100));
        ui->label_2->setMovie(losegif);
        losegif->start();
        qstrResult = "抱歉，你输了。";
    }
    return qstrResult;
}




game::~game()
{
    delete ui;
}

void game::on_pushButton_clicked()
{
    vector<QString> vec{filename1, filename2,filename3};
        int n = rand()%3;
        QString filename4 = vec[n];
        QImage* img=new QImage;
        if(! ( img->load(filename1) ) ) //加载图像
        {
        QMessageBox::information(this,tr("打开图像失败"),tr("打开图像失败!"));
        delete img;
        return;
        }
        ui->showImage->setPixmap(QPixmap::fromImage(*img));
        ui->showImage->setScaledContents(true);
        QImage* img1=new QImage;
        if(! ( img1->load(filename4) ) ) //加载图像
        {
        QMessageBox::information(this,tr("打开图像失败"),tr("打开图像失败!"));
        delete img1;
        return;
        }
        ui->showImage2->setPixmap(QPixmap::fromImage(*img1));
        ui->showImage2->setScaledContents(true);

        QString final = competition(filename1,filename4);
        ui->label_4->setText(final);
}

void game::on_pushButton_2_clicked()
{
    vector<QString> vec{filename1, filename2,filename3};
        int n = rand()%3;
        QString filename4 = vec[n];
        QImage* img=new QImage;
        if(! ( img->load(filename2) ) ) //加载图像
        {
        QMessageBox::information(this,tr("打开图像失败"),tr("打开图像失败!"));
        delete img;
        return;
        }
        ui->showImage->setPixmap(QPixmap::fromImage(*img));
        ui->showImage->setScaledContents(true);
        QImage* img1=new QImage;
        if(! ( img1->load(filename4) ) ) //加载图像
        {
        QMessageBox::information(this,tr("打开图像失败"),tr("打开图像失败!"));
        delete img1;
        return;
        }
        ui->showImage2->setPixmap(QPixmap::fromImage(*img1));
        ui->showImage2->setScaledContents(true);

        QString final = competition(filename2,filename4);
        ui->label_4->setText(final);
}

void game::on_pushButton_3_clicked()
{
    vector<QString> vec{filename1, filename2,filename3};
       int n = rand()%3;
       QString filename4 = vec[n];
       QImage* img=new QImage;
       if(! ( img->load(filename3) ) ) //加载图像
       {
       QMessageBox::information(this,tr("打开图像失败"),tr("打开图像失败!"));
       delete img;
       return;
       }
       ui->showImage->setPixmap(QPixmap::fromImage(*img));
       ui->showImage->setScaledContents(true);
       QImage* img1=new QImage;
       if(! ( img1->load(filename4) ) ) //加载图像
       {
       QMessageBox::information(this,tr("打开图像失败"),tr("打开图像失败!"));
       delete img1;
       return;
       }
       ui->showImage2->setPixmap(QPixmap::fromImage(*img1));
       ui->showImage2->setScaledContents(true);

       QString final = competition(filename3,filename4);
       ui->label_4->setText(final);
}
