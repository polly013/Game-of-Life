#ifndef BOARD_H
#define BOARD_H
#include<algorithm>

const int TableSize = 50;

class Board{
public:
    Board();
    bool getState (int i, int j) const;
    void change (int i, int j);
    void makeTurn ();
    void clear ();
    int generationNumber;
    int populationNumber;

private:
    int countNeighbours (int i, int j) const;
    int cells[2][TableSize][TableSize];
    bool currTurn;
};

#endif // BOARD_H
