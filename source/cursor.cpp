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
    if(!scene->bShowingBoard)
    {
        if(Widget* currWidget = scene->getCurrentWidget())
        {
            currWidget->onBack();
        }

        return;
    }
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

    if(!scene->bShowingBoard)
    {
        if(Widget* currWidget = scene->getCurrentWidget())
        {
            currWidget->onSelect();
        }

        return;
    }

    FCastQuery castQuery;
    castQuery.filteredObjects.push_back(this);

    if(Object* foundObject = scene->getObjectAtLocation(location, castQuery))
    {
        foundObject->destroy();
    }
}

void Cursor::bButtonLongClick(MicroBitEvent event)
{
    longPressed = true;

    if(!scene->bShowingBoard)
    {
        if(Widget* currWidget = scene->getCurrentWidget())
        {
            currWidget->onLongSelect();
        }

        return;
    }

    WPieceInfo* infoWidget = scene->createWidget<WPieceInfo>();

    FCastQuery castQuery;
    castQuery.filteredObjects.push_back(this);
    if(Object* foundObject = scene->getObjectAtLocation(location, castQuery))
    {
        if(Piece* piece = static_cast<Piece*>(foundObject))
        {
            infoWidget->init(piece);
            infoWidget->pushToViewport();
        }
    }
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

    if(!scene->bShowingBoard)
        return;

    elapsedTime += deltaTime;
    if(elapsedTime >= timeBetweenMovements)
    {
        handleMovement();
        elapsedTime = 0;
    }
}