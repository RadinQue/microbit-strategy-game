#include "cursor.h"
#include "fmath.h"
#include "scene.h"
#include "MicroBit.h"

Cursor::Cursor(Point location, Scene* scene)
{
    scene->getUBit()->messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_UP, this, &Cursor::aButtonUp);
    scene->getUBit()->messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_UP, this, &Cursor::bButtonUp);

    this->scene = scene;
    this->location = location;
}

void Cursor::aButtonUp(MicroBitEvent event)
{
    offset(Point(-1, 0));
}

void Cursor::bButtonUp(MicroBitEvent event)
{
    offset(Point(1, 0));
}

void Cursor::move(Point new_location)
{
    location = Point::clamp_screen(new_location);
    getScene()->updateScene();
}

void Cursor::offset(Point offset)
{
    location = Point::clamp_screen(location + offset);
    getScene()->updateScene();
}

void Cursor::tick()
{
    Object::tick();
}