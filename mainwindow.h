#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMenuBar>
#include <QMenu>

#include "gamegrid.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    GameGrid gameGrid;

    int makeMenu();

public slots:
    void quit();
    void showAbout();
};

#endif // MAINWINDOW_H
