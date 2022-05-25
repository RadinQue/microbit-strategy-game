#include "rook.h"
#include "MicroBitImage.h"


//remove
#include "scene.h"

Rook::Rook(const Point& location, Scene* scene)
{
    this->scene = scene;
    this->location = location;

    maxHealth = 8;
    maxAttack = 2;
}

bool Rook::canMoveAtLocation(const Point& location)
{
    possibleMoves.clear();
    for (int8_t i = 1; i <= 4; ++i)
    {
        scene->getUBit()->serial.printf("%d", i);
        // vertical
        possibleMoves.push_back(getLocation() + (getForwardVector() * i));
        possibleMoves.push_back(getLocation() + (getForwardVector() * -i));

        // horizontal
        possibleMoves.push_back(getLocation() + (getRightVector() * i));
        possibleMoves.push_back(getLocation() + (getRightVector() * -i));
    }
    
    return Piece::canMoveAtLocation(location);
}

MicroBitImage Rook::classImage()
{
    MicroBitImage image("\
                    255  0  255  0  255\n\
                    255 255 255 255 255\n\
                     0  255 255 255  0 \n\
                     0  255 255 255  0 \n\
                    255 255 255 255 255\n");

    return image;
}
