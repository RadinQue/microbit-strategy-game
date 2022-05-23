#include "pawn.h"

Pawn::Pawn(const Point& location, Scene* scene)
{
    this->scene = scene;
    this->location = location;
}

bool Pawn::canMoveAtLocation(const Point& location)
{
    
    return true;
}