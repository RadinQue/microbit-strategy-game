#ifndef PAWN_H
#define PAWN_H

#include "../piece.h"

class Pawn : public Piece
{
public:
    Pawn(const Point& location, Scene* scene);

    virtual void calculatePossibleMoves() override;
    virtual MicroBitImage classImage() override;

    virtual void start() override;

private:
};

#endif