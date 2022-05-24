#include "scene.h"

#include "object.h"
#include "fmath.h"
#include "widgets/widget.h"
#include "MicroBitImage.h"
#include "cursor.h"
#include "piece.h"
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

    // if we have a widget, draw it.
    // we always draw the last widget
    // this way it's easy to implement sub menus
    // that we can exit any time
    if(widgets.size() > 0)
    {
        bShowingBoard = false;

        uBit->display.setDisplayMode(DISPLAY_MODE_GREYSCALE);

        // do this when player 1's turn
        if(cursor->getCurrentPlayer()->side == ESide::Port)
            uBit->display.rotateTo(MICROBIT_DISPLAY_ROTATION_180);

        uBit->display.image.paste(widgets[widgets.size() - 1]->draw());

        return;
    }

    drawBoard();
}

void Scene::drawBoard()
{
    bShowingBoard = true;

    uBit->display.rotateTo(MICROBIT_DISPLAY_ROTATION_0);

    uBit->display.setDisplayMode(DISPLAY_MODE_GREYSCALE);

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

    for(Widget* wdg : widgets)
    {
        wdg->tick(sceneSpeed);
    }
}

void Scene::destroyObject(Object* object)
{
    if(!object)
        return;

    objects.erase(std::remove(objects.begin(), objects.end(), object));

    delete object;

    updateScene();
}

void Scene::destroyPiece(Piece* piece)
{
    if(!piece)
        return;

    piece->getOwner()->removePiece(piece);
    destroyObject(piece);
}

void Scene::switchTurnFrom(Player* currentPlayer)
{
    for (Player* player : players)
    {
        if(player != currentPlayer)
        {
            cursor->setCurrentPlayer(player);
            return;
        }
    }
}
