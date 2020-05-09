#ifndef SODOKU_SOLVER_SQUARE_H
#define SODOKU_SOLVER_SQUARE_H


class Square {
public:
    bool isSet();
    void removePossibilities(short valueMask);
    bool isValuePossible(short valueBit);
    void set(short valueBit);
    short getValueBit();
    short getPossibilityMask();

private:
    bool _isSet = false;
    short possibilitiesMask = 0b111111111;
    short valueBit = 0;
};


#endif //SODOKU_SOLVER_SQUARE_H
