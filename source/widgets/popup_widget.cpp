#include "popup_widget.h"

#include "../scene.h"

void PopupWidget::destroy()
{
    if(scene)
        scene->InputTarget = EInputTarget::EIT_Widgets;

    if(invoke)
        invoke(object, method);
        
    removeFromViewport();
}

void PopupWidget::pushToViewport()
{
    Widget::pushToViewport();

    if(scene)
        scene->InputTarget = EInputTarget::EIT_None;

    timeElapsed = 0;
    ticking = true;
}

MicroBitImage PopupWidget::draw()
{
    return MicroBitImage("\
                255 0 255 0 255\n\
                 0 255 0 255 0 \n\
                255 0 255 0 255\n\
                 0 255 0 255 0 \n\
                255 0 255 0 255\n");
}

void PopupWidget::tick(int deltaTime)
{
    if(!ticking)
        return;

    timeElapsed += deltaTime;
    if(timeElapsed >= duration)
        destroy();
}