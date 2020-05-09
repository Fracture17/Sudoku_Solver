#include "Common.h"


int rowAndColToIndex(int r, int c) {
    return r * COLS + c;
}


int indexToRow(int i) {
    return i / COLS;
}


int indexToCol(int i) {
    return i % COLS;
}


int indexToBoxStartRow(int i) {
    int r = indexToRow(i);
    return r - (r % BOX_HEIGHT);
}


int indexToBoxStartCol(int i) {
    int c = indexToCol(i);
    return c - (c % BOX_WIDTH);
}