#include "scene.h"

#include "object.h"
#include "fmath.h"
#include <algorithm>

Scene::Scene(/* args */)
{
    uBit = new MicroBit();
    uBit->init();
    uBit->display.setDisplayMode(DISPLAY_MODE_GREYSCALE);
}

Scene::~Scene()
{
    for (Object* obj : objects)
        delete obj;

    release_fiber();
}

void Scene::updateScene()
{
    uBit->display.clear();

    for (Object* object : objects)
    {
        Point location = object->getLocation();

        std::vector<Object*> objectsAtLocation = getObjectsAtLocation(location);
        Object* highestZOrderObject = object;
        for(Object* zOrderTest : objectsAtLocation)
        {
            if(zOrderTest->getZOrder() > highestZOrderObject->getZOrder())
                highestZOrderObject = zOrderTest;
        }
        int opacity = highestZOrderObject->getOpacity();

        uBit->display.image.setPixelValue(location.x, location.y, opacity);
    }
}

bool Scene::spaceOccupied(const Point& location, FCastQuery castQuery) const
{
    for (Object* obj : objects)
    {
        if(std::find(castQuery.filteredObjects.begin(), castQuery.filteredObjects.end(), obj) != castQuery.filteredObjects.end())
            continue;

        if (obj->getLocation() == location)
            return true;
    }

    return false;
}

std::vector<Object*> Scene::getObjectsAtLocation(const Point& location, FCastQuery castQuery) const
{
    std::vector<Object*> foundObjects;
    for(Object* obj : objects)
    {
        if(std::find(castQuery.filteredObjects.begin(), castQuery.filteredObjects.end(), obj) != castQuery.filteredObjects.end())
            continue;

        if(obj->getLocation() == location)
            foundObjects.push_back(obj);
    }

    return foundObjects;
}

Object* Scene::getObjectAtLocation(const Point& location, FCastQuery castQuery) const
{
    for (Object* obj : objects)
    {
        if(std::find(castQuery.filteredObjects.begin(), castQuery.filteredObjects.end(), obj) != castQuery.filteredObjects.end())
            continue;

        if(obj->getLocation() == location)
            return obj;
    }

    return nullptr;
}

void Scene::tick()
{
    for (Object* obj: objects)
    {
        obj->tick(sceneSpeed);
    }
}

void Scene::destroyObject(Object* object)
{
    if(!object)
        return;

    uBit->serial.printf("Size before removal: %d\n", objects.size());

    objects.erase(std::remove(objects.begin(), objects.end(), object));

    uBit->serial.printf("Size after removal: %d\n", objects.size());

    delete object;

    updateScene();
}