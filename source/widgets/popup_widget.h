#ifndef POPUP_WIDGET_H
#define POPUP_WIDGET_H

#include "widget.h"
#include "stdint.h"
#include <string.h>

class PopupWidget : public Widget
{
public:
    template<typename T>
    PopupWidget(int duration, T* object, void (T::*handler)())
    {
        this->duration = duration;
        this->object = object;
        memset(this->method, 0, sizeof(this->method));
        memcpy(this->method, &handler, sizeof(handler));
        invoke = &PopupWidget::methodCall<T>;
    }

    PopupWidget(int duration)
    {
        this->duration = duration;
    }

    PopupWidget() {}

    void setDuration(int duration)
    {
        this->duration = duration;
    }

    template <typename T> static void methodCall(void* object, __uint32_t*method);

    virtual MicroBitImage draw() override;
    virtual void tick(int deltaTime) override;
    virtual void pushToViewport() override;

protected:
    bool ticking = false;

    int duration;
    int timeElapsed;

    void* object;
    __uint32_t method[4];
    void (*invoke)(void *object, __uint32_t *method);

    void destroy();
};

template<typename T>
void PopupWidget::methodCall(void* object, __uint32_t* method)
{
    T* o = (T*)object;
    void (T::*m)();
    memcpy(&m, method, sizeof(m));

    (o->*m)();
}

#endif