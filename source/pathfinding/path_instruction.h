#ifndef PATH_INSTRUCTION_H
#define PATH_INSTRUCTION_H

#include <vector>
#include "../fmath.h"

struct PathInstruction
{
    PathInstruction();
    PathInstruction(const Point& _direction, uint8_t _range, bool _bPassThrough)
        : direction(_direction)
        , range(_range)
        , bPassThrough(_bPassThrough)
    {}

    Point direction;
    // -1 means indefinite
    int8_t range;

    // whether or not the piece can
    // pass through other pieces
    // (like the knight does in chess)
    bool bPassThrough;
};


#endif