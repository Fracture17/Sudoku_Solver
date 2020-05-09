#ifndef SODOKU_SOLVER_BOARDWRAPPER_H
#define SODOKU_SOLVER_BOARDWRAPPER_H

#include "Board.h"


class BoardWrapper {
public:
    BoardWrapper(const Board &board, int index);

    Board board;
    int index;
};


#endif //SODOKU_SOLVER_BOARDWRAPPER_H
