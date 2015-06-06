#ifndef AI_H
#define AI_H

#include "gobanggame.h"

class Ai
{
public:
    Ai(GobangGame *game);
    ~Ai();
    void setChessman();
    void setWho(int who);

private:
    /**
     * @brief _game 这个Ai是在为哪一盘棋做思考
     */
    GobangGame *_game;

    /**
     * @brief _who 电脑掌控哪方棋子，
     */
    int _who;

    /**
     * @brief getPos 计算应该在哪里下子
     * @return 下子的坐标，前两字节row，后两字节col
     */
    int getPos() const;

    /**
     * @brief getScore 在row行col列下子的价值分
     * @param row 行
     * @param col 列
     * @return 价值得分
     */
    int getScore(int row, int col) const;
};

#endif // AI_H
