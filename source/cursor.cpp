#include "cursor.h"
#include "fmath.h"
#include "scene.h"
#include "piece.h"
#include "MicroBit.h"

#define MOVEMENT_THRESHOLD 10

Cursor::Cursor(Point location, Scene* scene)
{
    // INPUT
    scene->getUBit()->messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_DOWN, this, &Cursor::aButtonDown);
    scene->getUBit()->messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_UP, this, &Cursor::aButtonUp);
    scene->getUBit()->messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_DOWN, this, &Cursor::bButtonDown);
    scene->getUBit()->messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_UP, this, &Cursor::bButtonUp);

    // SETUP
    this->scene = scene;
    this->location = location;
    opacity = 32;
    zOrder = 1;
}

void Cursor::aButtonDown(MicroBitEvent event)
{
    opacity = 255;
    scene->updateScene();
}

void Cursor::aButtonUp(MicroBitEvent event)
{
    opacity = 32;
    scene->updateScene();
}

void Cursor::bButtonDown(MicroBitEvent event)
{
    FCastQuery castQuery;
    castQuery.filteredObjects.push_back(this);

    if(Object* foundObject = scene->getObjectAtLocation(location, castQuery))
    {
        foundObject->destroy();
    }
}

void Cursor::bButtonUp(MicroBitEvent event)
{

}

void Cursor::move(Point new_location)
{
    location = Point::clamp_screen(new_location);
}

void Cursor::offset(Point offset)
{
    location = Point::clamp_screen(location + offset);
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

    elapsedTime += deltaTime;
    if(elapsedTime >= timeBetweenMovements)
    {
        handleMovement();
        elapsedTime = 0;
    }
}