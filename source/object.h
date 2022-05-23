#ifndef OBJECT_H
#define OBJECT_H

#include "fmath.h"

class Object
{
public:
    Object(/* args */);
    Object(Point location, class Scene* scene);

    Point getLocation() const { return location; }
    int getOpacity() const { return opacity; }
    
    virtual void tick();
    class Scene* getScene() const { return scene; }
    void setScene(Scene* newScene) { scene = newScene; }

protected:
    Point location;
    int opacity = 255;
    Scene* scene;
};

#endif