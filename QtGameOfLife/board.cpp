#include "board.h"

bool valid (int i, int j){
    if (i < 0 || j < 0) return false;
    if (i >= TableSize || j >= TableSize) return false;
    return true;
}

Board::Board(){
    for (int i = 0; i < TableSize; i++)
        for (int j = 0; j < TableSize; j++){
            cells[0][i][j] = 0;
            cells[1][i][j] = 0;
        }

    for (int j = 0 ; j < TableSize; j++)
        cells[0][j][j] = 1;

    currTurn = 0;
}

bool Board::state (int i, int j){
    return cells[currTurn][i][j];
}

void Board::change (int i, int j){
    cells[currTurn][i][j] ^= 1;
}

void Board::makeTurn(){
    for (int i = 0; i < TableSize; i++)
        for (int j = 0; j < TableSize; j++){
            int neighbours = getNeighbours(i, j);

            if (cells[currTurn][i][j] == 1){
                if (neighbours == 2 || neighbours == 3) cells[currTurn^1][i][j] = 1;
            }
            else{
                if (neighbours == 3) cells[currTurn^1][i][j] = 1;
            }
        }

    for (int i = 0; i < TableSize; i++)
        for (int j = 0; j < TableSize; j++)
            cells[currTurn][i][j] = 0;

    currTurn ^= 1;
}

int Board::getNeighbours(int i, int j){
    int neighbours = 0;

    if (valid (i-1, j)) neighbours += cells[currTurn][i-1][j];
    if (valid (i+1, j)) neighbours += cells[currTurn][i+1][j];
    if (valid (i, j+1)) neighbours += cells[currTurn][i][j+1];
    if (valid (i, j-1)) neighbours += cells[currTurn][i][j-1];

    if (valid (i-1, j+1)) neighbours += cells[currTurn][i-1][j+1];
    if (valid (i+1, j+1)) neighbours += cells[currTurn][i+1][j+1];
    if (valid (i-1, j-1)) neighbours += cells[currTurn][i-1][j-1];
    if (valid (i+1, j-1)) neighbours += cells[currTurn][i+1][j-1];

    return neighbours;
}
