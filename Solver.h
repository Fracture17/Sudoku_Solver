#ifndef SODOKU_SOLVER_SOLVER_H
#define SODOKU_SOLVER_SOLVER_H

#include "Board.h"
#include "BoardWrapper.h"
#include "Stack.h"


typedef void (*editBoard)(Board& board);


Board solve(Board& initialState, editBoard editFunc = nullptr);


#endif //SODOKU_SOLVER_SOLVER_H
