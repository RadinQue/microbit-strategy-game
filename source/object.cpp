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

void Object::tick(int deltaTime)
{

}

void Object::destroy()
{
    scene->destroyObject(this);
}