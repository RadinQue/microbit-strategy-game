#ifndef PLAYER_H
#define PLAYER_H

#include "fmath.h"
#include "object.h"

class Cursor : public Object
{
public:
    Cursor() {}
    Cursor(Point location, class Scene* scene);

    void aButtonUp(class MicroBitEvent event);
    void bButtonUp(class MicroBitEvent event);

    void move(Point new_location);
    void offset(Point offset);

    virtual void tick() override;

private:

};

#endif