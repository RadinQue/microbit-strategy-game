#ifndef KNIGHT_H
#define KNIGHT_H

#include "../piece.h"

class Knight : public Piece
{
public:
    Knight(const Point& location, Scene* scene);

    virtual void calculatePossibleMoves() override;
    virtual MicroBitImage classImage() override;

private:
};

#endif