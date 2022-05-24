#include "piece.h"
#include "player.h"
#include "scene.h"

Piece::Piece(const Point& location, Scene* scene)
{
    this->scene = scene;
    this->location = location;
}

bool Piece::canMoveAtLocation(const Point& location)
{
    for (Point loc : possibleMoves)
    {
        if(location == loc)
            return true;
    }

    return false;
}

void Piece::start()
{
    health = maxHealth;
    attack = maxAttack;
}

void Piece::destroy()
{
    scene->destroyPiece(this);
}

Point Piece::getForwardVector() const
{
    if(owner)
        return owner->side == ESide::Pins ? Point(0, -1) : Point(0, 1);

    return Point(0, 0);
}

Point Piece::getRightVector() const
{
    if(owner)
        return owner->side == ESide::Pins ? Point(1, 0) : Point(-1, 0);

    return Point(0, 0);
}

void Piece::dealDamage(Piece* target)
{
    if(!target)
        return;

    target->onDamageReceived(attack);
}

void Piece::onDamageReceived(int dmg, Piece* instigator/* = nullptr*/)
{
    health -= dmg;
}
