#include "Solver.h"


Board solve(Board& initialState, editBoard editFunc) {
    Stack<BoardWrapper> boardStack;
    boardStack.push(BoardWrapper(initialState, 0));
    bool finished = false;
    Board result;

#pragma omp parallel
    while(finished == false) {
        auto wrapper = boardStack.pop();
        auto& board = wrapper.board;
        int i = wrapper.index;

        if(editFunc != nullptr) {
            editFunc(board);
        }

        while(i < 81 && board.isSquareSet(i)) {
            i++;
        }
        if(i >= 81) {
            if(board.isValid()) {
                finished = true;
                result = board;
                //used to wake threads that may be waiting for the stack to become non-empty
                boardStack.push({result, 0});
            }
        }
        else {
            for (int n = 0; n < 9; ++n) {
                short value = 1 << n;
                if(board.isValuePossibleForCell(i, value)) {
                    Board newBoard = board;
                    newBoard.setCell(i, value);
                    boardStack.push(BoardWrapper(newBoard, i + 1));
                }

            }
        }
    }
    return result;
}