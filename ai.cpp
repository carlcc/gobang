#include "ai.h"
#include <stdlib.h>

Ai::Ai(GobangGame *game) :
    _game(game)
{
    _who = 1;
}

Ai::~Ai()
{
}

int Ai::getPos() const
{
    if (_game->getSteps() == 0) {
        int halfSize = _game->getGridLength()/2;
        return (rand()%5 + halfSize - 2 << 16) | (rand()%5 + halfSize - 2);
    }
    int i, j;
    char *map = _game->getMap();
    int length = _game->getGridLength();

    int maxrow = 0;
    int maxcol = 0;

    int maxscore = -1;
    int score;

    for (i = 0; i < length; i++)
        for (j = 0; j < length; j++) {
            if (map[i*length + j] == -1) {
                score = getScore(i, j);
                if (maxscore <= score) {
                    maxscore = score;
                    maxrow = i;
                    maxcol = j;
                }
            }
        }

    return (maxrow << 16) | maxcol;
}

int Ai::getScore(int row, int col) const
{
    if (_game->getMap()[row*_game->getGridLength() + col] != -1)
        return 0;

    int who = this->_who;

    int lines[4] = {
        _game->horizonalCount(row, col, who),
        _game->verticalCount(row, col, who),
        _game->slantCount(row, col, who),
        _game->backSlantCount(row, col, who)
    };
    who = !who;
    int linesE[4] = {
        _game->horizonalCount(row, col, who),
        _game->verticalCount(row, col, who),
        _game->slantCount(row, col, who),
        _game->backSlantCount(row, col, who)
    };

#define ACCESSIVES(A) ((A) & 0xffffff)
#define DEATHS(A) ((A) >> 24)

    int fives = 0;
    int liveFours = 0;
    int deadFours = 0;
    int liveThrees = 0;
    int deadThrees = 0;
    int liveTwos = 0;
    int deadTwos = 0;

    int fivesE = 0;
    int liveFoursE = 0;
    int deadFoursE = 0;
    int liveThreesE = 0;
    int deadThreesE = 0;
    int liveTwosE = 0;
    int deadTwosE = 0;

    int score = 0;

    int i;
    for (i = 0; i < 4; ++i)
        switch (ACCESSIVES(lines[i])) {
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            fives++;
            break;
        case 3:
            switch (DEATHS(lines[i])) {
            case 0:
                liveFours++;
                break;
            case 1:
                deadFours++;
                break;
            }
            break;
        case 2:
            switch (DEATHS(lines[i])) {
            case 0:
                liveThrees++;
                break;
            case 1:
                deadThrees++;
                break;
            }
            break;
        case 1:
            switch (DEATHS(lines[i])) {
            case 0:
                liveTwos++;
                break;
            case 1:
                deadTwos++;
                break;
            }
            break;
        }

    for (i = 0; i < 4; ++i)
        switch (ACCESSIVES(linesE[i])) {
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            fivesE++;
            break;
        case 3:
            switch (DEATHS(linesE[i])) {
            case 0:
                liveFoursE++;
                break;
            case 1:
                deadFoursE++;
                break;
            }
            break;
        case 2:
            switch (DEATHS(linesE[i])) {
            case 0:
                liveThreesE++;
                break;
            case 1:
                deadThreesE++;
                break;
            }
            break;
        case 1:
            switch (DEATHS(linesE[i])) {
            case 0:
                liveTwosE++;
                break;
            case 1:
                deadTwosE++;
                break;
            }
            break;
        }


    if (fives) {
        score += 6400000;
    }
    if (fivesE) {
        score += 3200000;
    }
    if (liveFours > 0 || deadFours >1 || (deadFours > 0 && liveThrees > 0)) {
        score += 1600000;
    }
    if (liveFoursE > 0 || deadFoursE >1 || (deadFoursE > 0 && liveThreesE > 0)) {
        score += 800000;
    }
    if (liveThrees > 1) {
        score += 400000;
    }
    if (liveThreesE > 1) {
        score += 200000;
    }
    if (liveThrees > 0 && deadThrees > 0) {
        score += 100000;
    }
    if (liveThreesE > 0 && deadThreesE > 0) {
        score += 80000;
    }
    if (deadFours > 0) {
        score += 50000;
    }
    if (deadFoursE > 0) {
        score += 30000;
    }
    if (liveThrees > 0) {
        score += 20000;
    }
    if (liveThreesE > 0) {
        score += 15000;
    }
    if (liveTwos > 1) {
        score += 10000;
    }
    if (liveTwosE > 1) {
        score += 8000;
    }
    if (deadThrees > 0) {
        score += 5000;
    }
    if (deadThreesE > 0) {
        score += 3000;
    }
    if (liveTwos > 0) {
        score += 2000;
    }
    if (liveTwosE > 0) {
        score += 1500;
    }
    if (deadTwos > 0) {
        score += 1000;
    }
    if (deadTwosE > 0) {
        score += 500;
    }

    return score;
}

void Ai::setChessman()
{
    int tmp = getPos();
    int row = tmp >> 16;
    int col = tmp & 0xffff;

    _game->setChessman(row, col);
}

void Ai::setWho(int who)
{
    this->_who = who;
}
