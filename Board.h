#ifndef SODOKU_SOLVER_BOARD_H
#define SODOKU_SOLVER_BOARD_H

#include <iostream>

#include "Square.h"
#include "Common.h"
#include "nmmintrin.h"


class Board {
public:
    explicit Board(short* initialState);
    Board() = default;

    void setCell(int i, short valueBit);
    void removeRowPossibilities(int r, short possibilitiesMask);
    void removeColPossibilities(int c, short possibilitiesMask);
    void removeBoxPossibilities(int boxStartR, int boxStartC, short possibilitiesMask);
    void removeCellPossibilities(int i, short possibilitiesMask);
    bool isValuePossibleForCell(int i, short valueBit);
    bool isSquareSet(int i);
    bool isValid();
    bool isGroupValid(int* group);
    short getCellPossibilityMask(int i);

    void display();

private:
    Square cells[ROWS * COLS];
};


#endif //SODOKU_SOLVER_BOARD_H
