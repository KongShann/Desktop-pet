#ifndef GAME_H
#define GAME_H

#include <QDialog>

#include <QString>
#include <QMessageBox>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>
#include <time.h>
#include <QMovie>

#include"ui_game.h"

namespace Ui {
class game;
}

class game : public QDialog
{
    Q_OBJECT

public:
    explicit game(QWidget *parent = nullptr);
    QString competition(QString man,QString computer);
    ~game();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::game *ui;
};

#endif // GAME_H
