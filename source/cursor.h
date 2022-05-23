#ifndef CURSOR_H
#define CURSOR_H

#include "fmath.h"
#include "object.h"

class MicroBitEvent;

class Cursor : public Object
{
public:
    Cursor() {}
    Cursor(Point location, class Scene* scene);

    void aButtonDown(MicroBitEvent event);
    void aButtonUp(MicroBitEvent event);

    void bButtonDown(MicroBitEvent event);
    void bButtonUp(MicroBitEvent event);

    void move(Point new_location);
    void offset(Point offset);

    class Player* getCurrentPlayer() const { return currentPlayer; }
    void setCurrentPlayer(Player* newPlayer) { currentPlayer = newPlayer; }

    void handleMovement();

    virtual void tick(int deltaTime) override;

private:
    int elapsedTime = 0;
    float timeBetweenMovements = 400;

    Player* currentPlayer;
};

#endif