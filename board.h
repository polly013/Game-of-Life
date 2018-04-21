#ifndef BOARD_H
#define BOARD_H
#include<algorithm>
#include<cstdio>
const int MaxTable = 50;

class board{
private:
    int Cells[2][MaxTable][MaxTable];
    bool currTurn;
public:
    board();
    int getNeighbours (int i, int j);
    void makeTurn ();
    void print ();
};

#endif // BOARD_H
