#ifndef W_DEBUG_H
#define W_DEBUG_H

#include "widget.h"

class WDebug : public Widget
{
public:
    WDebug(/* args */);

    virtual MicroBitImage draw() override;

private:
};



#endif