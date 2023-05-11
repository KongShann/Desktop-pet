#include "mainwindow.h"
#include "shopdress.h"
#include "appchoosewindow.h"
#include "calendarwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    MainWindow w;

    w.show();
    return a.exec();
}

