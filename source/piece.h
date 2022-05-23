#ifndef PIECE_H
#define PIECE_H

#include "object.h"

class Piece : public Object
{
public:
    Piece() {}
    Piece(const Point& location, Scene* scene);

    virtual bool canMoveAtLocation(const Point& location);

private:

};

#endif