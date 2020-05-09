#include "Board.h"


Board::Board(short *initialState) {
    for (int i = 0; i < 81; ++i) {
        if(initialState[i] != 0) {
            setCell(i, initialState[i]);
        }
    }
}


void Board::setCell(int i, short valueBit) {
    cells[i].set(valueBit);

    removeRowPossibilities(indexToRow(i), valueBit);
    removeColPossibilities(indexToCol(i), valueBit);
    removeBoxPossibilities(indexToBoxStartRow(i), indexToBoxStartCol(i), valueBit);
}


void Board::removeRowPossibilities(int r, short possibilitiesMask) {
    for (int c = 0; c < COLS; ++c) {
        int i = rowAndColToIndex(r, c);
        if(!cells[i].isSet()) {
            removeCellPossibilities(i, possibilitiesMask);
        }
    }
}


void Board::removeColPossibilities(int c, short possibilitiesMask) {
    for (int r = 0; r < ROWS; ++r) {
        int i = rowAndColToIndex(r, c);
        if(!cells[i].isSet()) {
            removeCellPossibilities(i, possibilitiesMask);
        }
    }
}


void Board::removeBoxPossibilities(int boxStartR, int boxStartC, short possibilitiesMask) {
    for (int r = 0; r < BOX_HEIGHT; ++r) {
        for (int c = 0; c < BOX_WIDTH; ++c) {
            int i = rowAndColToIndex(boxStartR + r, boxStartC + c);
            if(!cells[i].isSet()) {
                removeCellPossibilities(i, possibilitiesMask);
            }
        }
    }

}


void Board::removeCellPossibilities(int i, short possibilitiesMask) {
    cells[i].removePossibilities(possibilitiesMask);
}


bool Board::isSquareSet(int i) {
    return cells[i].isSet();
}


bool Board::isValuePossibleForCell(int i, short valueBit) {
    return cells[i].isValuePossible(valueBit);
}


bool Board::isValid() {
    int group[GROUP_SIZE];

    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            int i = rowAndColToIndex(r, c);
            group[c] = i;
        }

        if(isGroupValid(group) == false) {
            return false;
        }
    }

    for (int c = 0; c < COLS; ++c) {
        for (int r = 0; r < ROWS; ++r) {
            int i = rowAndColToIndex(r, c);
            group[r] = i;
        }

        if(isGroupValid(group) == false) {
            return false;
        }
    }

    for (int br = 0; br < ROW_BOXES; ++br) {
        for (int bc = 0; bc < COLUMN_BOXES; ++bc) {
            for (int r = 0; r < BOX_HEIGHT; ++r) {
                for (int c = 0; c < BOX_WIDTH; ++c) {
                    int i = rowAndColToIndex(br * BOX_HEIGHT + r, bc * BOX_WIDTH + c);
                    group[r * BOX_WIDTH + c] = i;
                }
            }

            if(isGroupValid(group) == false) {
                return false;
            }
        }
    }

    return true;
}


//counts how many cells have been set, and compares that to how many unique values there are
//if the number of unique values does not equal the number of set squares, there must be duplicates
bool Board::isGroupValid(int* group) {
    int setCount = 0;
    short setValuesMask = 0;
    for(int g = 0; g < GROUP_SIZE; g++) {
        int i = group[g];
        setCount += cells[i].isSet();
        setValuesMask |= cells[i].getValueBit();
    }
    return setCount == _mm_popcnt_u32(setValuesMask);
}


short Board::getCellPossibilityMask(int i) {
    return cells[i].getPossibilityMask();
}


void Board::display() {
    for(int r = 0; r < ROWS; r++) {
        for(int c = 0; c < COLS; c++) {
            short val = cells[r * COLS + c].getValueBit();
            if(val == 0) {
                std::cout << "0 ";
            }
            else {
                std::cout << (log2(val) + 1) << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}