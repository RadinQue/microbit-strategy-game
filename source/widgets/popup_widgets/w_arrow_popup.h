#ifndef W_ARROW_POPUP_H
#define W_ARROW_POPUP_H

#include "../popup_widget.h"

enum ESide : uint8_t;

class WArrowPopup : public PopupWidget
{
public:
    // template<typename T>
    // WArrowPopup(int duration, T* object, void (T::*handler)())
    // {
    //     this->duration = duration;
    //     this->object = object;
    //     memset(this->method, 0, sizeof(this->method));
    //     memcpy(this->method, &handler, sizeof(handler));
    //     invoke = &WArrowPopup::methodCall<T>;
    // }

    // WArrowPopup(int duration)
    // {
    //     this->duration = duration;
    // }

    // WArrowPopup()
    // {
    // }

    virtual MicroBitImage draw() override;
private:
};

#endif