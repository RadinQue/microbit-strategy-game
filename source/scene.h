#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "MicroBit.h"

class Object;
struct Point;

class Scene
{
public:
    Scene(/* args */);
    ~Scene();

    template<typename T>
    T* spawnObject(const Point& location)
    {
        if(spaceOccupied(location))
            return nullptr;
        
        T* newObject = new T(location, this);

        objects.push_back(newObject);

        updateScene();

        return newObject;
    }

    std::vector<Object*> getObjects() const { return objects; }

    bool spaceOccupied(const Point& location) const;

    void updateScene();
    bool isDirty() const { return dirty; }

    MicroBit* getUBit() { return uBit; }

    void tick();

private:
    std::vector<Object*> objects;

    bool dirty = false;

    MicroBit* uBit;
};


#endif