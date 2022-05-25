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

    void bButtonLongClick(MicroBitEvent event);
    void aButtonLongClick(MicroBitEvent event);

    class Player* getCurrentPlayer() const { return currentPlayer; }
    void setCurrentPlayer(Player* newPlayer) { currentPlayer = newPlayer; }

    void handleMovement();

    virtual void tick(int deltaTime) override;
    virtual EMessageType getMessageType() override { return EMessageType::EMT_Cursor; };

private:
    int elapsedTime = 0;
    float timeBetweenMovements = 400;

    Player* currentPlayer;

    bool longPressed = false;
};

#endif