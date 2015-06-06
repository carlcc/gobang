#include "gobanggame.h"

GobangGame::GobangGame(int gridLength) :
    _steps(0)
{
    int i;
    int len = gridLength * gridLength;
    _gridLength = gridLength;
    _history = new short[len];
    _map = new char[len];

    for (i = 0; i < len; ++i)
        _map[i] = (char)-1;
}

GobangGame::~GobangGame()
{
    delete [] _history;
    delete [] _map;
}

void GobangGame::reset()
{
    int i;
    int len = _gridLength * _gridLength;
    _steps = 0;

    for (i = 0; i < len; ++i)
        _map[i] = -1;
}

bool GobangGame::setChessman(int row, int col)
{
    if (_map[row*_gridLength + col] != -1)
        return false;
    _history[_steps] = (short)(row<<8 | col);
    _map[row*_gridLength + col] = _steps % 2;
    _steps++;
    return true;
}

int GobangGame::judge() const
{
    int row = (int)(_history[_steps-1] >> 8);
    int col = (int)(_history[_steps-1] & 0xff);
    int who = _map[row*_gridLength + col];


    if ((horizonalCount(row, col, who) & 0xffffff) >= 4 ||
            (verticalCount(row, col, who) & 0xffffff) >= 4 ||
            (slantCount(row, col, who) & 0xffffff) >= 4 ||
            (backSlantCount(row, col, who) & 0xffffff) >= 4)
        return who;

    if (_steps == _gridLength * _gridLength)
        return -1;
    return -2;
}

int GobangGame::getGridLength() const
{
    return _gridLength;
}

short *GobangGame::getHistory() const
{
    return _history;
}

int GobangGame::getSteps() const
{
    return _steps;
}

char *GobangGame::getMap() const
{
    return _map;
}

int GobangGame::readMap(int row, int col) const
{
    if (row < 0 || row >= _gridLength ||
            col < 0 || col >= _gridLength)
        return -2;
    return _map[row*_gridLength + col];
}

short GobangGame::readHistory(int i) const
{
    if (i < 0 || i >= _steps)
        return -1;
    return _history[i];
}

int GobangGame::horizonalCount(int row, int col, int who) const
{
    int count;
    int i;
    int death = 0;

    // 不用检查已经数了几个，如果数到的个数不少于5个
    // 说明之前就游戏结束（赢）了，不可能执行到这里

    // 自己和左边的同色棋子个数
    count = 0;
    for (i = col-1; i >= 0; --i)
        if (_map[row*_gridLength + i] == who)
            count++;
        else {
            if (_map[row*_gridLength + i] != -1)    // 如果是遇到对手棋子而终止
                death++;
            break;
        }
    if (i < 0)
        death++;

    // 右边同色棋子个数
    for (i = col+1; i < _gridLength; ++i)
        if (_map[row*_gridLength + i] == who)
            count++;
        else{
            if (_map[row*_gridLength + i] != -1)    // 如果是遇到对手棋子而终止
                death++;
            break;
        }
    if (i == _gridLength)
        death++;

    return count | (death << 24);
}

int GobangGame::verticalCount(int row, int col, int who) const
{
    int i, count;
    int death = 0;

    count = 0;
    // 自己和上边的同色棋子数
    for (i = row-1; i >= 0; --i)
        if (_map[i*_gridLength + col] == who)
            count++;
        else {
            if (_map[i*_gridLength + col] != -1)    // 如果是遇到对手棋子而终止
                death++;
            break;
        }
    if (i < 0)
        death++;
    // 下边的同色棋子数
    for (i = row+1; i < _gridLength; ++i)
        if (_map[i*_gridLength + col] == who)
            count++;
        else {
            if (_map[i*_gridLength + col] != -1)    // 如果是遇到对手棋子而终止
                death++;
            break;
        }
    if (i == _gridLength)
        death++;

    return count | (death << 24);
}

int GobangGame::backSlantCount(int row, int col, int who) const
{
    int i, j, count;
    int death = 0;

    count = 0;
    for (i = row-1, j = col-1; i >= 0 && j >= 0; --i, --j)
        if (_map[i*_gridLength + j] == who)
            count++;
        else {
            if (_map[i*_gridLength + j] != -1)
                death++;
            break;
        }
    if (i < 0 || j < 0)
        death++;

    for (i = row+1, j = col+1; i < _gridLength && j < _gridLength; ++i, ++j)
        if (_map[i*_gridLength + j] == who)
            count++;
        else {
            if (_map[i*_gridLength + j] != -1)
                death++;
            break;
        }
    if (i == _gridLength || j == _gridLength)
        death++;

    return count | (death << 24);
}

int GobangGame::slantCount(int row, int col, int who) const
{
    int i, j, count;
    int death = 0;

    count = 0;
    for (i = row-1, j = col+1; i >= 0 && j < _gridLength; --i, ++j)
        if (_map[i*_gridLength +j] == who)
            count++;
        else {
            if (_map[i*_gridLength +j] != -1)
                death++;
            break;
        }
    if (i < 0 || j == _gridLength)
        death++;

    for (i = row+1, j = col-1; i < _gridLength && j >= 0; ++i, --j)
        if (_map[i*_gridLength +j] == who)
            count++;
        else {
            if (_map[i*_gridLength +j] != -1)
                death++;
            break;
        }
    if (i == _gridLength || j < 0)
        death++;

    return count | (death << 24);
}

bool GobangGame::undo()
{
    if (_steps < 2) {   // 一次悔2步（对手一步自己一步），如果总共不到2步则没得悔
        return false;
    }
    int row, col;
    short hist;

    this->_steps--;
    hist = _history[_steps];
    row = hist >> 8;
    col = hist & 0xff;
    _map[row * _gridLength + col] = -1;

    this->_steps--;
    hist = _history[_steps];
    row = hist >> 8;
    col = hist & 0xff;
    _map[row * _gridLength + col] = -1;

    return true;
}
