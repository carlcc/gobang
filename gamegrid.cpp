#include "gamegrid.h"

GameGrid::GameGrid(int gridLength, int gridSize, QWidget *parent) :
    QWidget(parent),
    _game(gridLength),
    _gridSize(gridSize),
    _ai(&_game),
    _ai2(&_game),
    isPlaying(false)
{
    int totalLength = gridSize * gridLength;
    this->resize(totalLength, totalLength);
}

void GameGrid::mousePressEvent(QMouseEvent *event)
{
    if (isPlaying)  {
        int row = event->y() / _gridSize;
        int col = event->x() / _gridSize;

        if (event->button() == Qt::LeftButton)
            if (_game.readMap(row, col) != -1)
                return;
            else
                _game.setChessman(row, col);
        else
            _ai2.setChessman();
        update();
        switch (_game.judge()) {
        case -2:
            // 继续，轮到电脑
            _ai.setChessman();
            update();
            switch (_game.judge()) {
            case -2:
                // 继续，轮到人，可以推出函数了
                return;
            case 0:
                // 黑胜
                QMessageBox::information(this, tr("Game Over"), tr("Black Win!"));
                break;
            case 1:
                // 黑负
                QMessageBox::information(this, tr("Game Over"), tr("White Win!"));
                break;
            case -1:
                // 平局
                QMessageBox::information(this, tr("Game Over"), tr("Draw Game!"));
                break;
            }
            break;
        case 0:
            // 黑胜
            QMessageBox::information(this, tr("Game Over"), tr("Black Win!"));
            break;
        case 1:
            // 黑负
            QMessageBox::information(this, tr("Game Over"), tr("White Win!"));
            break;
        case -1:
            // 平局
            QMessageBox::information(this, tr("Game Over"), tr("Draw Game!"));
            break;
        }
        isPlaying = false;
    }
}

void GameGrid::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    paint.setPen(Qt::black);

    int i;
    int gridLength = _game.getGridLength();
    int halfSize1 = _gridSize/2;
    int halfSize2 = _gridSize - halfSize1;
    int totalLength = _gridSize * gridLength - halfSize2;

    for (i = 0; i < gridLength; ++i) {
        paint.drawLine(halfSize1, halfSize1 + i*_gridSize, totalLength, halfSize1 + i*_gridSize);
        paint.drawLine(halfSize1 + i*_gridSize, halfSize1, halfSize1 + i*_gridSize, totalLength);
    }

    int row, col;
    int history;
    int steps = _game.getSteps();
    for (i = 0; i < steps; ++i) {
        history = _game.readHistory(i);
        row = history >> 8;
        col = history & 0xff;
        if (i % 2) {
            paint.setPen(Qt::white);
            paint.setBrush(Qt::white);
            paint.drawEllipse(QPoint(halfSize1 + col*_gridSize, halfSize1 + row*_gridSize), halfSize1, halfSize1);
        } else {
            paint.setPen(Qt::black);
            paint.setBrush(Qt::black);
            paint.drawEllipse(QPoint(halfSize1 + col*_gridSize, halfSize1 + row*_gridSize), halfSize1, halfSize1);
        }
    }
    history = _game.readHistory(steps-1);
    row = history >> 8;
    col = history & 0xff;
    paint.setPen(Qt::red);
    paint.drawEllipse(QPoint(halfSize1 + col*_gridSize, halfSize1 + row*_gridSize), halfSize1, halfSize1);

}

void GameGrid::startGame()
{
    _game.reset();
    _ai.setWho(1);
    _ai2.setWho(0);
    isPlaying = true;
    update();
}

void GameGrid::startGame2()
{
    _game.reset();
    _ai.setWho(0);
    _ai2.setWho(1);
    _ai.setChessman();
    isPlaying = true;
    update();
}

void GameGrid::stopGame()
{
    isPlaying = false;
}

void GameGrid::undo()
{
    if (isPlaying) {
        _game.undo();
        update();
    }
}
