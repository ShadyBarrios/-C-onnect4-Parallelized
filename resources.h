#ifndef _RESOURCES_H_
#define _RESOURCES_H_
using namespace std;

extern const int rows, columns;
extern int board[7][7];

extern const int* rowPointers[7][7];
extern const int* colPointers[7][7];

extern const int* dPointers1[2][7];
extern const int* dPointers2[4][6];
extern const int* dPointers3[4][5];
extern const int* dPointers4[4][4];

extern const int** pointers[28];

extern const int lengths[28];

#endif