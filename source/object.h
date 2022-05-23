#ifndef OBJECT_H
#define OBJECT_H

#include "fmath.h"

class Object
{
public:
    Object(/* args */);
    Object(Point location, class Scene* scene);
    virtual ~Object();

    Point getLocation() const { return location; }
    int getOpacity() const { return opacity; }
    int getZOrder() const { return zOrder; }

    void setOpacity(int opacity) { this->opacity = opacity; }
    
    virtual void tick(int deltaTime);
    class Scene* getScene() const { return scene; }
    void setScene(Scene* newScene) { scene = newScene; }

    void destroy();

protected:
    Point location;
    int opacity = 255;
    int zOrder = 0;
    Scene* scene;
};

#endif