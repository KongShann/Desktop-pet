#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);
    Qt::WindowFlags m_flags = windowFlags();
    setWindowFlags(m_flags|Qt::WindowStaysOnTopHint);
    pet_appearance=new QLabel(this);
    SelectAppearance();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pet_appearance;
}
void MainWindow::SelectAppearance(){
    pet_appearance->resize(175,150);
    pet_appearance->setPixmap(QPixmap(":/resources/static/default.png").scaled(pet_appearance->size()));
}

void MainWindow::mousePressEvent(QMouseEvent *event)  {
        // 记录鼠标按下时的位置
    if (event->button() == Qt::LeftButton) {
               m_dragging = true;
               m_startPos = event->globalPos() - frameGeometry().topLeft();
                pet_appearance->setPixmap(QPixmap(":/resources/static/default2.png").scaled(pet_appearance->size()));
           }
    }

void MainWindow::mouseMoveEvent(QMouseEvent *event)  {
        // 移动窗口位置
    if (m_dragging) {
                move(event->globalPos() - m_startPos);

      pet_appearance->setPixmap(QPixmap(":/resources/static/default2.png").scaled(pet_appearance->size()));
            }
    }


void MainWindow::mouseReleaseEvent(QMouseEvent *event)
  {
      if (event->button() == Qt::LeftButton) {
          m_dragging = false;
           pet_appearance->setPixmap(QPixmap(":/resources/static/default.png").scaled(pet_appearance->size()));
      }
  }
