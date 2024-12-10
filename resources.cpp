#include "resources.h"

const int rows = 7, columns = 7;
int board[7][7] = {
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0}
};

const int* rowPointers[7][7] = {
    {&board[0][0], &board[0][1], &board[0][2], &board[0][3], &board[0][4], &board[0][5], &board[0][6]},
    {&board[1][0], &board[1][1], &board[1][2], &board[1][3], &board[1][4], &board[1][5], &board[1][6]},
    {&board[2][0], &board[2][1], &board[2][2], &board[2][3], &board[2][4], &board[2][5], &board[2][6]},
    {&board[3][0], &board[3][1], &board[3][2], &board[3][3], &board[3][4], &board[3][5], &board[3][6]},
    {&board[4][0], &board[4][1], &board[4][2], &board[4][3], &board[4][4], &board[4][5], &board[4][6]},
    {&board[5][0], &board[5][1], &board[5][2], &board[5][3], &board[5][4], &board[5][5], &board[5][6]},
    {&board[6][0], &board[6][1], &board[6][2], &board[6][3], &board[6][4], &board[6][5], &board[6][6]},
};

const int* colPointers[7][7] = {
    {&board[0][0], &board[1][0], &board[2][0], &board[3][0], &board[4][0], &board[5][0], &board[6][0]},
    {&board[0][1], &board[1][1], &board[2][1], &board[3][1], &board[4][1], &board[5][1], &board[6][1]},
    {&board[0][2], &board[1][2], &board[2][2], &board[3][2], &board[4][2], &board[5][2], &board[6][2]},
    {&board[0][3], &board[1][3], &board[2][3], &board[3][3], &board[4][3], &board[5][3], &board[6][3]},
    {&board[0][4], &board[1][4], &board[2][4], &board[3][4], &board[4][4], &board[5][4], &board[6][4]},
    {&board[0][5], &board[1][5], &board[2][5], &board[3][5], &board[4][5], &board[5][5], &board[6][5]},
    {&board[0][6], &board[1][6], &board[2][6], &board[3][6], &board[4][6], &board[5][6], &board[6][6]}
};

// size 7 diagonals
const int* dPointers1[2][7] = {
    {&board[0][0], &board[1][1], &board[2][2], &board[3][3], &board[4][4], &board[5][5], &board[6][6]},
    {&board[6][0], &board[5][1], &board[4][2], &board[3][3], &board[2][4], &board[1][5], &board[0][6]}
};  

// size 6 diagonals
const int* dPointers2[4][6] = {
    {&board[0][1], &board[1][2], &board[2][3], &board[3][4], &board[4][5], &board[5][6]},
    {&board[1][0], &board[2][1], &board[3][2], &board[4][3], &board[5][4], &board[6][5]},
    {&board[0][5], &board[1][4], &board[2][3], &board[3][2], &board[4][1], &board[5][0]},
    {&board[1][6], &board[2][5], &board[3][4], &board[4][3], &board[5][2], &board[6][1]}
};

// size 5 diagonals
const int* dPointers3[4][5] = {
    {&board[0][2], &board[1][3], &board[2][4], &board[3][5], &board[4][6]},
    {&board[2][0], &board[3][1], &board[4][2], &board[5][3], &board[6][4]},
    {&board[0][4], &board[1][3], &board[2][2], &board[3][1], &board[4][0]},
    {&board[2][6], &board[3][5], &board[4][4], &board[5][3], &board[6][2]}
};

// size 4 diagonals
const int* dPointers4[4][4] = {
    {&board[0][3], &board[1][2], &board[2][1], &board[3][0]},
    {&board[0][3], &board[1][4], &board[2][5], &board[3][6]},
    {&board[3][0], &board[4][1], &board[5][2], &board[6][3]},
    {&board[3][6], &board[4][5], &board[5][4], &board[6][3]}
};

const int** pointers[28] = {
    rowPointers[0], rowPointers[1], rowPointers[2], rowPointers[3], rowPointers[4], rowPointers[5], rowPointers[6],
    colPointers[0], colPointers[1], colPointers[2], colPointers[3], colPointers[4], colPointers[5], colPointers[6],
    dPointers1[0], dPointers1[1],
    dPointers2[0], dPointers2[1], dPointers2[2], dPointers2[3],
    dPointers3[0], dPointers3[1], dPointers3[2], dPointers3[3],
    dPointers4[0], dPointers4[1], dPointers4[2], dPointers4[3]
};

const int lengths[28] = {
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,  
    6, 6, 6, 6,                                      
    5, 5, 5, 5,                                       
    4, 4, 4, 4                                        
};