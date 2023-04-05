#include "mainwindow.h"
#include "shopdress.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    shopDress w;
    w.show();
    return a.exec();
}
