#include "widget.h"

#include "MicroBitImage.h"
#include "scene.h"

Widget::Widget()
{
}

MicroBitImage Widget::draw()
{
    return MicroBitImage();

}

void Widget::tick(int deltaTime)
{
}

void Widget::pushToViewport()
{
    if(!scene)
        return;

    scene->pushWidgetToViewport(this);
}
