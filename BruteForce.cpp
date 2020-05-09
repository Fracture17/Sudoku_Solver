#include "BruteForce.h"


Board solveBruteForce(Board& initialState) {
    Stack<BoardWrapper> boardStack;
    boardStack.push(BoardWrapper(initialState, 0));
    bool finished = false;
    Board result;

#pragma omp parallel
    while(finished == false) {
        auto wrapper = boardStack.pop();
        auto& board = wrapper.board;
        int i = wrapper.index;
        while(i < 81 && board.isSquareSet(i)) {
            i++;
        }
        if(i >= 81) {
            if(board.isValid()) {
                finished = true;
                result = board;
            }
        }
        else {
            for (int n = 0; n < 9; ++n) {
                short value = 1 << n;
                Board newBoard = board;
                newBoard.setCell(i, value);
                boardStack.push(BoardWrapper(newBoard, i + 1));
            }
        }

    }
    return result;
}