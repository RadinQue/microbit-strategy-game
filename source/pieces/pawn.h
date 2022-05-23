#ifndef PAWN_H
#define PAWN_H

#include "../piece.h"

class Pawn : public Piece
{
public:
    Pawn(const Point& location, Scene* scene);

    virtual bool canMoveAtLocation(const Point& location) override;
    virtual MicroBitImage classImage() override;

private:
};

#endif