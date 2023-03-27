#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setText("111");
//    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);
//    setAttribute(Qt::WA_TranslucentBackground);
//   Qt::WindowFlags m_flags = windowFlags();
//    setWindowFlags(m_flags|Qt::WindowStaysOnTopHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}

