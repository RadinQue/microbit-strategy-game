#ifndef ROOK_H
#define ROOK_H

#include "../piece.h"

class Rook : public Piece
{
public:
    Rook(const Point& location, Scene* scene);

    virtual void calculatePossibleMoves() override;
    virtual MicroBitImage classImage() override;

private:
};


#endif