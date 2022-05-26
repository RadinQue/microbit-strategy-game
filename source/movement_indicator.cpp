#include "movement_indicator.h"

MovementIndicator::MovementIndicator(const Point& loc, Scene* scene)
{
    this->scene = scene;
    this->location = loc;
    this->bHasCollision = false;
}

void MovementIndicator::tick(int deltaTime)
{
    blinkTimer += deltaTime / 100;
    if(blinkTimer >= blinkInterval)
    {
        setVisibility(!bVisible);
        blinkTimer = 0;
    }
}