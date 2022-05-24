#ifndef WIDGET_H
#define WIDGET_H

class MicroBitImage;
class Scene;

class Widget
{
public:
    Widget(/* args */);
    
    virtual MicroBitImage draw();
    virtual void tick(int deltaTime);
    virtual void onSelect() {}
    virtual void onLongSelect() {}
    virtual void onBack() {}
    virtual void onLongBack() {}
    void setScene(Scene* newScene) { scene = newScene; }

    void pushToViewport();

protected:
    Scene* scene;
};

#endif