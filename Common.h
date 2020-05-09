#ifndef SODOKU_SOLVER_COMMON_H
#define SODOKU_SOLVER_COMMON_H

#include <cmath>


const int GROUP_SIZE = 9;
const int ROWS = GROUP_SIZE;
const int COLS = GROUP_SIZE;
const int TOTAL_SQUARES = ROWS * COLS;
const int BOX_HEIGHT = (int)(sqrt(ROWS));
const int BOX_WIDTH = (int)(sqrt(COLS));
const int ROW_BOXES = ROWS / BOX_HEIGHT;
const int COLUMN_BOXES = COLS / BOX_WIDTH;


int rowAndColToIndex(int r, int c);
int indexToRow(int i);
int indexToCol(int i);
int indexToBoxStartRow(int i);
int indexToBoxStartCol(int i);


#endif //SODOKU_SOLVER_COMMON_H
