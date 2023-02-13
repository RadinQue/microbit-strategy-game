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

Piece::~Piece()
{
    destroyMoveIndicators();
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
    attributes.push_back(&health);
    attributes.push_back(&attack);
    attributes.push_back(&maxHealth);
    attributes.push_back(&maxAttack);
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

    target->onDamageReceived(attack.value);
}

void Piece::onDamageReceived(int dmg, Piece* instigator/* = nullptr*/)
{
    health.value -= dmg;
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

// Status System

void Piece::ApplyStatusEffectToSelf(StatusSystem::StatusEffect* effect)
{
    ApplyEffect(effect);
    
    if(effect->timingPolicy == StatusSystem::ETimingPolicy::TP_Instant)
        return;

    activeEffects.push_back(effect);
}

void Piece::RemoveStatusEffectFromSelf(StatusSystem::StatusEffect* effect)
{
    auto foundEffect = std::find(activeEffects.begin(), activeEffects.end(), effect);
    if(foundEffect != activeEffects.end())
    {
        RevertEffect(*foundEffect);
    }
}

void Piece::RemoveStatusEffectFromTarget(StatusSystem::StatusEffect* effect, Piece* target)
{
    if(!target)
        return;

    target->RemoveStatusEffectFromSelf(effect);
}

void Piece::TickEffect(StatusSystem::StatusEffect* effect)
{
    if(effect->timingPolicy == StatusSystem::ETimingPolicy::TP_Duration)
    {
        effect->duration--;
        return;
    }

    if(effect->timingPolicy == StatusSystem::ETimingPolicy::TP_Instant)
    {
        ApplyEffect(effect);
        return;
    }
}

void Piece::ApplyEffect(StatusSystem::StatusEffect* effect)
{
    for (const StatusSystem::FModifier& modifier : effect->modifiers)
    {
        auto foundAttribute = std::find_if(attributes.begin(), attributes.end(), [&modifier] (const StatusSystem::FAttribute* att)
        {
            return att->name == modifier.attributeName;
        });
        if(foundAttribute != attributes.end())
            ApplyModifierOnAttribute(modifier, *foundAttribute);
    }
}

void Piece::RevertEffect(StatusSystem::StatusEffect* effect)
{
    for (const StatusSystem::FModifier& modifier : effect->modifiers)
    {
        auto foundAttribute = std::find_if(attributes.begin(), attributes.end(), [&modifier] (const StatusSystem::FAttribute* att)
        {
            return att->name == modifier.attributeName;
        });
        if(foundAttribute != attributes.end())
            RevertModifierOnAttribute(modifier, *foundAttribute);
    }
}

void Piece::ApplyModifierOnAttribute(const StatusSystem::FModifier& modifier, StatusSystem::FAttribute* attribute)
{
    switch (modifier.operation)
    {
    case StatusSystem::Add:
        attribute->value += modifier.magnitude;
        break;

    case StatusSystem::Multiply:
        attribute->value *= modifier.magnitude;
        break;

    case StatusSystem::Divide:
        attribute->value /= modifier.magnitude;
        break;

    case StatusSystem::Override:
        attribute->value = modifier.magnitude;
        break;
    
    default:
        break;
    }
}

void Piece::RevertModifierOnAttribute(const StatusSystem::FModifier& modifier, StatusSystem::FAttribute* attribute)
{
    switch (modifier.operation)
    {
    case StatusSystem::Add:
        attribute->value += modifier.magnitude;
        break;

    case StatusSystem::Multiply:
        attribute->value *= modifier.magnitude;
        break;

    case StatusSystem::Divide:
        attribute->value /= modifier.magnitude;
        break;

    case StatusSystem::Override:
        attribute->value = attribute->baseValue;
        break;
    
    default:
        break;
    }
}

// -- Status System
