#include "Crooks.h"


Board solveCrooks(Board& initialState) {
    return solve(initialState, applyCrooks);
}


void applyCrooks(Board& board) {
    while(true) {
        if(applyEliminations(board)) {
            continue;
        }
        if(applyLoneRanger(board)) {
            continue;
        }
        if(applyHiddenPairs(board)) {
            continue;
        }
        break;
    }
}


bool applyEliminations(Board& board) {
    bool wasElimination = false;
    for (int i = 0; i < TOTAL_SQUARES; ++i) {
        if(board.isSquareSet(i) == false) {
            short possibilityMask = board.getCellPossibilityMask(i);
            int numPossibilities = _mm_popcnt_u32(possibilityMask);
            if(numPossibilities == 1) {
                board.setCell(i, possibilityMask);
                wasElimination = true;
            }
        }
    }
    return wasElimination;
}


bool applyLoneRanger(Board& board) {
    bool wasLoneRanger = false;
    int group[GROUP_SIZE];

    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            int i = rowAndColToIndex(r, c);
            group[c] = i;
        }
        wasLoneRanger |= applyLoneRangerInGroup(board, group);
    }

    for (int c = 0; c < COLS; ++c) {
        for (int r = 0; r < ROWS; ++r) {
            int i = rowAndColToIndex(r, c);
            group[r] = i;
        }
        wasLoneRanger |= applyLoneRangerInGroup(board, group);
    }

    for (int br = 0; br < ROW_BOXES; ++br) {
        for (int bc = 0; bc < COLUMN_BOXES; ++bc) {
            for (int r = 0; r < BOX_HEIGHT; ++r) {
                for (int c = 0; c < BOX_WIDTH; ++c) {
                    int i = rowAndColToIndex(br * BOX_HEIGHT + r, bc * BOX_WIDTH + c);
                    group[r * BOX_WIDTH + c] = i;
                }
            }

            wasLoneRanger |= applyLoneRangerInGroup(board, group);
        }
    }

    return wasLoneRanger;
}


bool applyLoneRangerInGroup(Board& board, int* group) {
    bool wasLoneRanger = false;
    for (int n = 0; n < 9; ++n) {
        short valueBit = 1 << n;
        wasLoneRanger |= applyLoneRangerInGroupForValueBit(board, group, valueBit);
    }
    return wasLoneRanger;
}


bool applyLoneRangerInGroupForValueBit(Board& board, int* group, short valueBit) {
    int encounterPosition = -1;
    for (int g = 0; g < GROUP_SIZE; ++g) {
        int i = group[g];
        if(board.isSquareSet(i) == false) {
            if (board.isValuePossibleForCell(i, valueBit)) {
                if (encounterPosition != -1) {
                    return false;
                }
                encounterPosition = i;
            }
        }
    }
    if(encounterPosition != -1) {
        board.setCell(encounterPosition, valueBit);
        return true;
    }
    return false;
}


bool applyHiddenPairs(Board& board) {
    bool wasBoardChanged = false;
    int group[GROUP_SIZE];

    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            int i = rowAndColToIndex(r, c);
            group[c] = i;
        }
        wasBoardChanged |= applyHiddenPairsInGroup(board, group);
    }

    for (int c = 0; c < COLS; ++c) {
        for (int r = 0; r < ROWS; ++r) {
            int i = rowAndColToIndex(r, c);
            group[r] = i;
        }
        wasBoardChanged |= applyHiddenPairsInGroup(board, group);
    }

    for (int br = 0; br < ROW_BOXES; ++br) {
        for (int bc = 0; bc < COLUMN_BOXES; ++bc) {
            for (int r = 0; r < BOX_HEIGHT; ++r) {
                for (int c = 0; c < BOX_WIDTH; ++c) {
                    int i = rowAndColToIndex(br * BOX_HEIGHT + r, bc * BOX_WIDTH + c);
                    group[r * BOX_WIDTH + c] = i;
                }
            }

            wasBoardChanged |= applyHiddenPairsInGroup(board, group);
        }
    }

    return wasBoardChanged;
}


bool applyHiddenPairsInGroup(Board& board, int* group) {
    bool wasBoardChanged = false;
    for (int g = 0; g < GROUP_SIZE; ++g) {
        int i = group[g];
        if(not board.isSquareSet(i)) {
            short cellPossibilitiesMask = board.getCellPossibilityMask(i);
            int numCellPossibilities = _mm_popcnt_u32(cellPossibilitiesMask);
            if(numCellPossibilities == 2) {
                for (int g2 = g + 1; g2 < GROUP_SIZE; ++g2) {
                    int j = group[g2];
                    if(board.getCellPossibilityMask(j) == cellPossibilitiesMask) {
                        wasBoardChanged |= removeHiddenPairPossibilities(board, group, i, j);
                    }
                }
            }
        }
    }
    return wasBoardChanged;
}


bool removeHiddenPairPossibilities(Board& board, int* group, int i, int j) {
    bool wasBoardChanged = false;
    short cellPossibilitiesMask = board.getCellPossibilityMask(i);
    for (int g = 0; g < GROUP_SIZE; ++g) {
        int k = group[g];
        if(k != i && k != j) {
            if(board.getCellPossibilityMask(k) & cellPossibilitiesMask) {
                wasBoardChanged = true;
                board.removeCellPossibilities(k, cellPossibilitiesMask);
            }
        }
    }
    return wasBoardChanged;
}