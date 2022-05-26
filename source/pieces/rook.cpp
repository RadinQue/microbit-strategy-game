#include "rook.h"
#include "pathfinding/path_instruction.h"
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

void Rook::calculatePossibleMoves()
{
    std::vector<PathInstruction> instructions;

    instructions.push_back(PathInstruction(getForwardVector(), -1, false));
    instructions.push_back(PathInstruction(getForwardVector() *= -1, -1, false));
    instructions.push_back(PathInstruction(getRightVector(), -1, false));
    instructions.push_back(PathInstruction(getRightVector() *= -1, -1, false));

    Piece::calculatePossibleMoves(instructions);
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
