#ifndef PIECE_H
#define PIECE_H

#include "object.h"
#include <vector>

class MicroBitImage;
class Scene;

class Piece : public Object
{
public:
    Piece() {}
    Piece(const Point& location, Scene* scene);

    virtual bool canMoveAtLocation(const Point& location);
    bool canPutPieceOn(const Point& location);
    virtual void calculatePossibleMoves() = 0;
    virtual void calculatePossibleMoves(const std::vector<struct PathInstruction>& instructions);

    void spawnMoveIndicators();
    void destroyMoveIndicators();

    virtual MicroBitImage classImage() = 0;

    virtual void start() override;
    virtual void destroy() override;

    int8_t getHealth() const { return health; }
    int8_t getAttack() const { return attack; }

    int8_t getMaxHealth() const { return maxHealth; }
    int8_t getMaxAttack() const { return maxAttack; }

    void dealDamage(Piece* target);
    void onDamageReceived(int dmg, Piece* instigator = nullptr);

    Point getForwardVector() const;
    Point getRightVector() const;
    void setOwner(class Player* player) { owner = player; }
    Player* getOwner() const { return owner; }

    virtual EMessageType getMessageType() override { return EMessageType::EMT_Piece; };

protected:
    int8_t health;
    int8_t attack;

    int8_t maxHealth;
    int8_t maxAttack;

    Player* owner;

    std::vector<Point> possibleMoves;
    std::vector<class MovementIndicator*> moveIndicators;

};

#endif