#include "scene.h"

#include "object.h"
#include "fmath.h"

Scene::Scene(/* args */)
{
    uBit = new MicroBit();

    uBit->init();
}

Scene::~Scene()
{
    release_fiber();
}

void Scene::updateScene()
{
    uBit->display.clear();

    for (Object* object : objects)
    {
        Point location = object->getLocation();
        int opacity = object->getOpacity();

        uBit->display.image.setPixelValue(location.x, location.y, opacity);
    }
}

bool Scene::spaceOccupied(const Point& location) const
{
    for (Object* obj : objects)
    {
        if (obj->getLocation() == location)
            return true;
    }

    return false;
}

void Scene::tick()
{
    for (Object* obj: objects)
    {
        obj->tick();
    }
}