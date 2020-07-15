#ifndef GAME_H
#define GAME_H

#include <QPoint>
#include <iostream>
#include <stdlib.h>
#include <time.h>

class Game
{
public:
    Game();
    ~Game();

    QPoint getSize();
    int getSizeRect();
    char** getMap();
    int getScoreBot();
    int getScorePlayer();

    bool IsLeftMove();
    bool IsWinner();

    void setPoint(int row, int col, char turn);
    void setOnceBotPlayer(bool oncePlayerBot);

    void updateScoreBot();
    void updateScorePlayer();
    void update();
    void updateOtherBot();
    char getPoint(int row, int col);
    void reset();
    int evelution(char** map, bool bot = false);

    const char SYM_0 = '0';
    const char SYM_X = 'X';
    const int NEG_INF = -10000;
    const int POS_INF = 10000;
    const int MIN = 10;
    const int MAX = -10;

private:
    int minimax(char** map, bool turn, bool bot = false);
    void nextMove(char** map, bool bot = false);
    void setArea(int rows, int cols);
    void clearArea();
    void displayMatrix(char** map);

    QPoint* size;
    QPoint bestPoint;
    int sizeRect;
    char** map;

    int scoreBot;
    int scorePlayer;

    bool oncePlayerBot;
    bool onceBot;
};

#endif // GAME_H
