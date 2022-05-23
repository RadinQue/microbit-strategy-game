#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <chrono>
#include <ctime>
#include "player.h"
#include "types/cast_types.h"
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

    void destroyObject(Object* object);

    std::vector<Object*> getObjects() const { return objects; }

    bool spaceOccupied(const Point& location, FCastQuery castQuery = FCastQuery()) const;
    std::vector<Object*> getObjectsAtLocation(const Point& location, FCastQuery castQuery = FCastQuery()) const;
    Object* getObjectAtLocation(const Point& location, FCastQuery castQuery = FCastQuery()) const;

    void updateScene();
    bool isDirty() const { return dirty; }

    MicroBit* getUBit() { return uBit; }

    void tick();

    int sceneSpeed = 100;

    template<class T>
    T* grantPlayerPiece(const Point& location, Player* player)
    {
        T* newPiece = spawnObject<T>(location);
        player->addPiece(newPiece);
        return newPiece;
    }

private:
    std::vector<Object*> objects;
    bool dirty = false;
    MicroBit* uBit;
};


#endif