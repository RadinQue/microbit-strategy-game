#include "pawn.h"
#include "MicroBitImage.h"




Pawn::Pawn(const Point& location, Scene* scene)
{
    this->scene = scene;
    this->location = location;

    maxHealth = 6;
    maxAttack = 9;
}

void Pawn::start()
{
    Piece::start();

}

bool Pawn::canMoveAtLocation(const Point& location)
{
    possibleMoves.clear();
    possibleMoves.push_back(getLocation() + getForwardVector());

    return Piece::canMoveAtLocation(location);
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
