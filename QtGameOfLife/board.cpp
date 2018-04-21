#include "board.h"

bool valid (int i, int j){
    if (i < 0 || j < 0) return false;
    if (i >= MaxTable || j >= MaxTable) return false;
    return true;
}

board::board(){
    for (int i = 0; i < MaxTable; i++)
        for (int j = 0; j < MaxTable; j++){
            scanf ("%d", &Cells[0][i][j]);
            Cells[1][i][j] = 0;
        }

    currTurn = 0;
}

void board::makeTurn(){
    for (int i = 0; i < MaxTable; i++)
        for (int j = 0; j < MaxTable; j++){
            int neighbours = getNeighbours(i, j);

            if (Cells[currTurn][i][j] == 1){
                if (neighbours == 2 || neighbours == 3) Cells[currTurn^1][i][j] = 1;
            }
            else{
                if (neighbours == 3) Cells[currTurn^1][i][j] = 1;
            }
        }

    for (int i = 0; i < MaxTable; i++)
        for (int j = 0; j < MaxTable; j++)
            Cells[currTurn][i][j] = 0;

    currTurn ^= 1;
}

int board::getNeighbours(int i, int j){
    int neighbours = 0;

    if (valid (i-1, j)) neighbours += Cells[currTurn][i-1][j];
    if (valid (i+1, j)) neighbours += Cells[currTurn][i+1][j];
    if (valid (i, j+1)) neighbours += Cells[currTurn][i][j+1];
    if (valid (i, j-1)) neighbours += Cells[currTurn][i][j-1];

    if (valid (i-1, j+1)) neighbours += Cells[currTurn][i-1][j+1];
    if (valid (i+1, j+1)) neighbours += Cells[currTurn][i+1][j+1];
    if (valid (i-1, j-1)) neighbours += Cells[currTurn][i-1][j-1];
    if (valid (i+1, j-1)) neighbours += Cells[currTurn][i+1][j-1];

    return neighbours;
}

void board::print (){
    printf ("\n");
    for (int i = 0; i < MaxTable; i++){
        for (int j = 0; j < MaxTable; j++){
            printf ("%d ", Cells[currTurn][i][j]);
        }
    printf ("\n");
    }

    printf ("\n");
}

int main (){
    board proba;

    for (int i = 0; i < 5; i ++){
        proba.makeTurn();
        proba.print();
    }
}
