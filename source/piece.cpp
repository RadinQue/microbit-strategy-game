#include "piece.h"

Piece::Piece(const Point& location, Scene* scene)
{
    this->scene = scene;
    this->location = location;
}

bool Piece::canMoveAtLocation(const Point& location)
{
    return false;
}