#include "cursor.h"
#include "fmath.h"
#include "scene.h"
#include "piece.h"
#include "widgets/w_piece_info.h"
#include "MicroBit.h"

#define MOVEMENT_THRESHOLD 10

Cursor::Cursor(Point location, Scene* scene)
{
    // INPUT
    scene->getUBit()->messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_DOWN, this, &Cursor::aButtonDown);
    scene->getUBit()->messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_UP, this, &Cursor::aButtonUp);
    scene->getUBit()->messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_DOWN, this, &Cursor::bButtonDown);
    scene->getUBit()->messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_UP, this, &Cursor::bButtonUp);
    scene->getUBit()->messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_HOLD, this, &Cursor::bButtonLongClick);
    scene->getUBit()->messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_HOLD, this, &Cursor::aButtonLongClick);

    // SETUP
    this->scene = scene;
    this->location = location;
    opacity = 32;
    zOrder = 1;
    longPressed = false;
}

void Cursor::aButtonDown(MicroBitEvent event)
{
}

void Cursor::aButtonUp(MicroBitEvent event)
{
    if(longPressed)
    {
        longPressed = false;
        return;
    }

    if(!currentPlayer)
        return;

    currentPlayer->onButtonA();
}

void Cursor::bButtonDown(MicroBitEvent event)
{
}

void Cursor::bButtonUp(MicroBitEvent event)
{
    if(longPressed)
    {
        longPressed = false;
        return;
    }

    if(!currentPlayer)
        return;

    currentPlayer->onButtonB();
}

void Cursor::bButtonLongClick(MicroBitEvent event)
{
    longPressed = true;

    if(!currentPlayer)
        return;

    currentPlayer->onLongButtonB();
}

void Cursor::aButtonLongClick(MicroBitEvent event)
{
    longPressed = true;

    if(!currentPlayer)
        return;

    currentPlayer->onLongButtonA();
}

void Cursor::handleMovement()
{
    int roll = scene->getUBit()->accelerometer.getRoll();
    int pitch = scene->getUBit()->accelerometer.getPitch();

    if(roll > MOVEMENT_THRESHOLD)
        offset(Point(1, 0));

    if(roll < -MOVEMENT_THRESHOLD)
        offset(Point(-1, 0));

    if(pitch > MOVEMENT_THRESHOLD)
        offset(Point(0, 1));

    if(pitch < -MOVEMENT_THRESHOLD)
        offset(Point(0, -1));
}

void Cursor::tick(int deltaTime)
{
    Object::tick(deltaTime);

    if(!scene->bShowingBoard)
        return;

    elapsedTime += deltaTime;
    if(elapsedTime >= timeBetweenMovements)
    {
        handleMovement();
        elapsedTime = 0;
    }
}