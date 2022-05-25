#ifndef OBJECT_H
#define OBJECT_H

#include "fmath.h"
#include "types/message_types.h"

class Object
{
public:
    Object(/* args */);
    Object(Point location, class Scene* scene);
    virtual ~Object();

    void move(Point new_location);
    void offset(Point offset);

    Point getLocation() const { return location; }
    uint8_t getOpacity() const;
    uint8_t getZOrder() const { return zOrder; }

    void setOpacity(int opacity) { this->opacity = opacity; }
    void setVisibility(bool visible);
    
    virtual void start();
    virtual void tick(int deltaTime);
    class Scene* getScene() const { return scene; }
    void setScene(Scene* newScene) { scene = newScene; }

    virtual void destroy();

    virtual EMessageType getMessageType() { return EMessageType::EMT_Object; };

protected:
    Point location;
    uint8_t opacity = 16;
    uint8_t zOrder = 0;
    Scene* scene;

    bool bVisible = true;
};

#endif