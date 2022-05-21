#include "player.h"
#include "fmath.h"

Player::Player()
{
    location.x = 2;
    location.y = 2;
}

Player::Player(int x, int y)
{
    location.x = x;
    location.y = y;
}

Player::~Player()
{
}

void Player::move(Point new_location)
{
    location = Point::clamp_screen(new_location);
}

void Player::offset(Point offset)
{
    location = Point::clamp_screen(location + offset);
}