#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <chrono>
#include <ctime>
#include "player.h"
#include "types/cast_types.h"
#include "MicroBit.h"

class Object;
class Piece;
class Widget;
struct Point;

enum class EInputTarget : uint8_t
{
    EIT_Board,
    EIT_Widgets,
    EIT_None
};

class Scene
{
public:
    Scene(/* args */);
    ~Scene();

    template<typename T>
    T* createWidget()
    {
        T* newWidget = new T();
        newWidget->setScene(this);
        return newWidget;
    }

    template<typename T, typename Obj>
    T* createPopupWidget(int duration, Obj* object, void (Obj::*handler)())
    {
        T* newWidget = new T(duration, object, handler);
        newWidget->setScene(this);
        return newWidget;
    }

    template<typename T>
    T* createPopupWidget(int duration)
    {
        T* newWidget = new T(duration);
        newWidget->setScene(this);
        return newWidget;
    }

    void pushWidgetToViewport(Widget* widget)
    {
        widgets.push_back(widget);
    }

    void removeWidget()
    {
        widgets.pop_back();
    }

    void removeWidgetFromViewport(Widget* widget);

    Widget* getCurrentWidget() const
    {
        if(widgets.size() > 0)
            return widgets[widgets.size() - 1];

        return nullptr;
    }

    template<typename T>
    T* spawnObject(const Point& location)
    {
        T* newObject = new T(location, this);
        objects.push_back(newObject);

        newObject->start();

        updateScene();

        return newObject;
    }

    Player* createPlayer(ESide side)
    {
        Player* newPlayer = new Player(this, side);
        players.push_back(newPlayer);

        return newPlayer;
    }

    void destroyObject(Object* object);
    void destroyPiece(Piece* piece);

    std::vector<Object*> getObjects() const { return objects; }

    bool spaceOccupied(const Point& location, FCastQuery castQuery = FCastQuery()) const;
    std::vector<Object*> getObjectsAtLocation(const Point& location, FCastQuery castQuery = FCastQuery()) const;
    Object* getObjectAtLocation(const Point& location, FCastQuery castQuery = FCastQuery()) const;
    Object* getObjectAtLocationOfType(const Point& location, EMessageType type) const;

    void updateScene();
    bool isDirty() const { return dirty; }

    MicroBit* getUBit() { return uBit; }

    void tick();

    int sceneSpeed = 100;

    template<class T>
    T* grantPlayerPiece(const Point& location, Player* player)
    {
        T* newPiece = spawnObject<T>(location);

        newPiece->setOwner(player);

        player->addPiece(newPiece);
        return newPiece;
    }

    void setCursor(class Cursor* newCursor) { cursor = newCursor; }
    Cursor* getCursor() const { return cursor; }

    bool bShowingBoard = true;
    EInputTarget InputTarget;

    void switchTurnFrom(Player* currentPlayer);

private:
    void drawBoard();

    std::vector<Object*> objects;
    std::vector<Widget*> widgets;
    std::vector<Player*> players;
    bool dirty = false;
    MicroBit* uBit;

    Cursor* cursor;
};


#endif