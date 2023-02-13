#ifndef PIECE_H
#define PIECE_H

#include "object.h"
#include "status_system/status_types.h"
#include <vector>

class MicroBitImage;
class Scene;

class Piece : public Object
{
public:
    Piece() {}
    Piece(const Point& location, Scene* scene);
    ~Piece();

    virtual bool canMoveAtLocation(const Point& location);
    bool canPutPieceOn(const Point& location);
    virtual void calculatePossibleMoves() = 0;
    virtual void calculatePossibleMoves(const std::vector<struct PathInstruction>& instructions);

    void spawnMoveIndicators();
    void destroyMoveIndicators();

    virtual MicroBitImage classImage() = 0;

    virtual void start() override;
    virtual void destroy() override;

    int8_t getHealth() const { return health.value; }
    int8_t getAttack() const { return attack.value; }

    int8_t getMaxHealth() const { return maxHealth.value; }
    int8_t getMaxAttack() const { return maxAttack.value; }

    StatusSystem::FAttribute& getHealthAttribute() { return health; }
    StatusSystem::FAttribute& getAttackAttribute() { return attack; }
    StatusSystem::FAttribute& getMaxHealthAttribute() { return maxHealth; }
    StatusSystem::FAttribute& getMaxAttackAttribute() { return maxAttack; }

    void dealDamage(Piece* target);
    void onDamageReceived(int dmg, Piece* instigator = nullptr);

    Point getForwardVector() const;
    Point getRightVector() const;
    void setOwner(class Player* player) { owner = player; }
    Player* getOwner() const { return owner; }

    virtual EMessageType getMessageType() override { return EMessageType::EMT_Piece; };

    // Status System

    void ApplyStatusEffectToSelf(StatusSystem::StatusEffect* effect);
    void ApplyStatusEffectToTarget(StatusSystem::StatusEffect* effect, Piece* target);
    void RemoveStatusEffectFromSelf(StatusSystem::StatusEffect* effect);
    void RemoveStatusEffectFromTarget(StatusSystem::StatusEffect* effect, Piece* target);

    // -- Status System

protected:
    StatusSystem::FAttribute health;
    StatusSystem::FAttribute attack;

    StatusSystem::FAttribute maxHealth;
    StatusSystem::FAttribute maxAttack;

    Player* owner;

    std::vector<Point> possibleMoves;
    std::vector<class MovementIndicator*> moveIndicators;

    // Status System

    std::vector<StatusSystem::StatusEffect*> activeEffects;

    // -- Status System

private:
    // Status System

    std::vector<StatusSystem::FAttribute*> attributes;

    void TickEffect(StatusSystem::StatusEffect* effect);
    void ApplyEffect(StatusSystem::StatusEffect* effect);
    void RevertEffect(StatusSystem::StatusEffect* effect);
    void ApplyModifierOnAttribute(const StatusSystem::FModifier& modifier, StatusSystem::FAttribute* attribute);
    void RevertModifierOnAttribute(const StatusSystem::FModifier& modifier, StatusSystem::FAttribute* attribute);

    // -- Status System

};

#endif