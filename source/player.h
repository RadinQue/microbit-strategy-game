#ifndef PLAYER_H
#define PLAYER_H

#include "fmath.h"

class Player
{
public:
    Player();
    Player(int x, int y);
    ~Player();

    void move(Point new_location);
    void offset(Point offset);

    Point get_location() const { return location; }

private:
    Point location;

};

#endif