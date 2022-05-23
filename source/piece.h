#ifndef PIECE_H
#define PIECE_H

#include "object.h"

class MicroBitImage;

class Piece : public Object
{
public:
    Piece() {}
    Piece(const Point& location, Scene* scene);

    virtual bool canMoveAtLocation(const Point& location);
    virtual MicroBitImage classImage() = 0;

    uint8_t getHealth() const { return health; }
    uint8_t getMagic() const { return magic; }

protected:
    uint8_t health;
    uint8_t magic;

};

#endif