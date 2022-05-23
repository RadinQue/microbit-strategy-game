#include "w_debug.h"

#include "MicroBitImage.h"

WDebug::WDebug(/* args */)
{
}

MicroBitImage WDebug::draw()
{
    MicroBitImage image("\
        0 0 1 0 0\n\
        0 1 1 1 0\n\
        1 0 1 0 1\n\
        0 0 1 0 0\n\
        0 0 1 0 0\n");

    return image;
}
