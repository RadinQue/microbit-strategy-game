#include "piece.h"
#include "player.h"
#include "scene.h"
#include "movement_indicator.h"
#include "pathfinding/pathfinder.h"

Piece::Piece(const Point& location, Scene* scene)
{
    this->scene = scene;
    this->location = location;
}

bool Piece::canMoveAtLocation(const Point& location)
{
    possibleMoves.clear();
    calculatePossibleMoves();

    for (Point loc : possibleMoves)
    {
        if(location == loc)
            return true;
    }

    return false;
}

bool Piece::canPutPieceOn(const Point& location)
{
    return std::find(possibleMoves.begin(), possibleMoves.end(), location) != possibleMoves.end();
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

void Piece::calculatePossibleMoves(const std::vector<PathInstruction>& instructions)
{
    possibleMoves = Pathfinder::calculateDestinations(scene, this, instructions);
}

void Piece::spawnMoveIndicators()
{
    calculatePossibleMoves();
    for(const Point& loc : possibleMoves)
    {
        MovementIndicator* newObj = scene->spawnObject<MovementIndicator>(loc);
        newObj->setOpacity(8);
        moveIndicators.push_back(newObj);
    }
}

void Piece::destroyMoveIndicators()
{
    for(MovementIndicator* obj : moveIndicators)
    {
        if(obj)
            obj->destroy();
    }

    moveIndicators.clear();
}
