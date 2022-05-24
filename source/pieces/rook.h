#ifndef ROOK_H
#define ROOK_H

#include "../piece.h"

class Rook : public Piece
{
public:
    Rook(const Point& location, Scene* scene);

    virtual bool canMoveAtLocation(const Point& location) override;
    virtual MicroBitImage classImage() override;

private:
};


#endif