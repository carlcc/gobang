#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    gameGrid(15, 30, this)
{
    int height = makeMenu();
    gameGrid.move(15, height);// + ui->menuBar->height());
    this->resize(gameGrid.width() + 30,height+gameGrid.height() + 10);
}

MainWindow::~MainWindow()
{
}

int MainWindow::makeMenu()
{
    QMenuBar * MenuBar = new QMenuBar(this);
    QMenu * GameMenu = new QMenu(tr("Game(&G)"), MenuBar);
    QMenu * AlgorithmMenu = new QMenu(tr("Algorithm(&A)"), MenuBar);
    QMenu * HelpMenu = new QMenu(tr("Help(&H)"), MenuBar);

    //添加游戏菜单项
    QAction * StartGame = new QAction(tr("Start(&S)"), GameMenu);
    QAction * StartGame2 = new QAction(tr("Start(Computer first)"), GameMenu);
    QAction * StopGame = new QAction(tr("End(&E)"), GameMenu);
    QAction * QuitGame = new QAction(tr("Quit(&Q)"), GameMenu);
    QAction * Undo = new QAction(tr("Undo(&Z)"), GameMenu);

    GameMenu->addAction(Undo);
    GameMenu->addAction(StartGame);
    GameMenu->addAction(StartGame2);
    GameMenu->addAction(StopGame);
    GameMenu->addAction(QuitGame);
    MenuBar->addMenu(GameMenu);

    //添加帮助菜单
    QAction * About = new QAction(tr("About"), HelpMenu);
    HelpMenu->addAction(About);
    MenuBar->addMenu(HelpMenu);


    //设置菜单栏
    setMenuBar(MenuBar);

    connect(Undo, SIGNAL(triggered()), &gameGrid, SLOT(undo()));
    connect(StartGame, SIGNAL(triggered()), &gameGrid, SLOT(startGame()));
    connect(StartGame2, SIGNAL(triggered()), &gameGrid, SLOT(startGame2()));
    connect(StopGame, SIGNAL(triggered()), &gameGrid, SLOT(stopGame()));
    connect(QuitGame, SIGNAL(triggered()), this, SLOT(quit()));
    connect(About, SIGNAL(triggered()), this, SLOT(showAbout()));

    return MenuBar->height();
}

void MainWindow::quit()
{
    exit(0);
}

void MainWindow::showAbout()
{
    QMessageBox::information(this, tr("About"), tr("A simple gobang game. \nAuthor: Chen Chen. 2014.4.15"));
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    gameGrid.undo();
}
