#ifndef GAMEGRID_H
#define GAMEGRID_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include "ai.h"
#include "gobanggame.h"

class GameGrid : public QWidget
{
    Q_OBJECT
public:
    explicit GameGrid(int gridLength = 15, int gridSize = 20, QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    /** 游戏后台内容 */
    GobangGame _game;

    /** Ai 棋手 */
    Ai _ai;
    Ai _ai2;
    /** 棋盘每个格子的大小（像素） */
    int _gridSize;

    bool isPlaying;

public slots:
    void stopGame();
    void startGame();
    void startGame2();
    void undo();
    
};

#endif // GAMEGRID_H
