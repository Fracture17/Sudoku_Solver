#ifndef SODOKU_SOLVER_CROOKS_H
#define SODOKU_SOLVER_CROOKS_H

#include "Board.h"
#include "Common.h"
#include "Solver.h"


Board solveCrooks(Board& initialState);
void applyCrooks(Board& board);
bool applyEliminations(Board& board);
bool applyLoneRanger(Board& board);
bool applyLoneRangerInGroup(Board& board, int* group);
bool applyLoneRangerInGroupForValueBit(Board& board, int* group, short valueBit);
bool applyHiddenPairs(Board& board);
bool applyHiddenPairsInGroup(Board& board, int* group);
bool removeHiddenPairPossibilities(Board& board, int* group, int i, int j);


#endif //SODOKU_SOLVER_CROOKS_H
