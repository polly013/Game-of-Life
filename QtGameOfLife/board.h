#ifndef BOARD_H
#define BOARD_H
#include<algorithm>
#include<cstdio>

const int TableSize = 50;

class Board{
public:
    Board();
    int getNeighbours (int i, int j);
    bool state (int i, int j);
    void change (int i, int j);
    void makeTurn ();
private:
    int cells[2][TableSize][TableSize];
    bool currTurn;
};

#endif // BOARD_H
