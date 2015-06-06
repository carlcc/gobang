#ifndef GOBANGGAME_H
#define GOBANGGAME_H

class GobangGame
{
public:
    GobangGame(int gridLength);
    ~GobangGame();

    /** 重置游戏 */
    void reset();

    /**
     * 在第row行第col列下子，自动判断该哪方下子
     * 如果下子成功返回true，否则false.
     */
    bool setChessman(int row, int col);

    /**
     * @brief undo 悔棋
     * @return 成功悔棋返回true，否则（如已经到了第一步）false
     */
    bool undo();

    /**
     * 判断胜负
     * 最后下子者胜返回0
     * 最后下子者负返回1
     * 平局返回-1
     * 否则(未分胜负且游戏未结束)返回-2
     */
    int judge() const;

    int getGridLength() const;
    short *getHistory() const;
    /**
     * @brief readHistory 获取第i步的记录
     * @param i 第i手棋，从0开始记
     * @return 第i手棋所在的坐标，第一字节表示行，第二字节表示列.如果i非法，则返回-1（坐标是(255,255)）
     */
    short readHistory(int i) const;
    int getSteps() const;
    char *getMap() const;
    /**
     * @brief readMap，返回棋盘第row行第col列的值
     * @param row 行
     * @param col 列
     * @return -1表示空，0表示黑，1表示白，-2表示行或列非法
     */
    int readMap(int row, int col) const;

private:
    /**
     * 棋盘的线条数(棋盘大小)
     */
    int _gridLength;
    /**
     * 下子历史（int数组，实际上和_steps配合是一个栈）,第一个字节为row，第二个字节为col
     */
    short *_history;
    /**
     * （双方）已经下了多少步
     */
    int _steps;
    /**
     * 二维数组棋盘状态, -1表示空，0表示黑，1表示白
     * 该变量只用于快速访问，本身其实是一个冗余的变量
     */
    char *_map;

    /**
     * @brief horizonalCount 如果第row行col列下who的子，水平方向的连子数
     * @param row 行
     * @param col 列
     * @param who 下子方
     * @return 最高字节指示有几端（0,1或2）被堵住，后面3字节表示连子数-1
     */
    int horizonalCount(int row, int col, int who) const;
    /**
     * @brief verticalCount 如果第row行col列下who的子，竖直方向的连子数
     * @param row 行
     * @param col 列
     * @param who 下子方
     * @return 最高字节指示有几端（0,1或2）被堵住，后面3字节表示连子数-1
     */
    int verticalCount(int row, int col, int who) const;
    /**
     * @brief slantCount 如果第row行col列下who的子，正斜(\)方向的连子数
     * @param row 行
     * @param col 列
     * @param who 下子方
     * @return 最高字节指示有几端（0,1或2）被堵住，后面3字节表示连子数-1
     */
    int slantCount(int row, int col, int who) const;
    /**
     * @brief backSlantCount 如果第row行col列下who的子，反斜(/)方向的连子数
     * @param row 行
     * @param col 列
     * @param who 下子方
     * @return 最高字节指示有几端（0,1或2）被堵住，后面3字节表示连子数-1
     */
    int backSlantCount(int row, int col, int who) const;

    friend class Ai;
};

#endif // GOBANGGAME_H
