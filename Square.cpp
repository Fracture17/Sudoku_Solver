#include "Square.h"


bool Square::isSet() {
    return _isSet;
}


void Square::removePossibilities(short valueMask) {
    possibilitiesMask &= ~valueMask;
}


bool Square::isValuePossible(short valueBit) {
    return valueBit & possibilitiesMask;
}


void Square::set(short valueBit) {
    this->valueBit = valueBit;
    possibilitiesMask = valueBit;
    _isSet = true;
}


short Square::getValueBit() {
    return valueBit;
}


short Square::getPossibilityMask() {
    return possibilitiesMask;
}
