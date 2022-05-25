#ifndef MOVEMENT_INDICATOR_H
#define MOVEMENT_INDICATOR_H

#include "object.h"

class MovementIndicator : public Object
{
public:
    MovementIndicator(const Point& loc, Scene* scene);

    virtual void tick(int deltaTime) override;

private:
    // milliseconds / 100
    // (5 will be 500ms)
    uint8_t blinkInterval = 5;
    uint8_t blinkTimer = 0;
};

#endif