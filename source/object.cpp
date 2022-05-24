#include "object.h"
#include "scene.h"

Object::Object(/* args */)
{
}

Object::Object(Point location, Scene* scene)
{
    this->scene = scene;
    this->location = location;
}

Object::~Object()
{
}

void Object::start()
{

}

void Object::tick(int deltaTime)
{

}

void Object::destroy()
{
    scene->destroyObject(this);
}

uint8_t Object::getOpacity() const
{
    return bVisible ? opacity : 0;
}

void Object::setVisibility(bool visible)
{
    bVisible = visible;
}

void Object::move(Point new_location)
{
    location = Point::clamp_screen(new_location);
}

void Object::offset(Point offset)
{
    location = Point::clamp_screen(location + offset);
}
