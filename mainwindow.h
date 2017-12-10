/*
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "player.h"

#include <SFML/Graphics.hpp>

class MainWindow{
public:
    MainWindow(Player* p);

private:
    Player player;
    void movePlayer();
    void start();
};

#endif // MAINWINDOW_H
