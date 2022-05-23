#include "object.h"

Object::Object(/* args */)
{
}

Object::Object(Point location, Scene* scene)
{
    this->scene = scene;
    this->location = location;
}

void Object::tick()
{

}