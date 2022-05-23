#include "pawn.h"
#include "MicroBitImage.h"

Pawn::Pawn(const Point& location, Scene* scene)
{
    this->scene = scene;
    this->location = location;

    health = 6;
    magic = 9;
}

bool Pawn::canMoveAtLocation(const Point& location)
{

    return true;
}

MicroBitImage Pawn::classImage()
{
    MicroBitImage image("\
                    255  0  255  0  255\n\
                    255  0  255  0  255\n\
                    255 255 255 255 255\n\
                     0   0  255  0   0 \n\
                     0   0  255  0   0 \n");

    return image;
}
