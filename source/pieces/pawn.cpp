#include "pawn.h"
#include "pathfinding/path_instruction.h"
#include "MicroBitImage.h"


Pawn::Pawn(const Point& location, Scene* scene)
{
    this->scene = scene;
    this->location = location;

    maxHealth = 3;
    maxAttack = 2;
}

void Pawn::start()
{
    Piece::start();

}

void Pawn::calculatePossibleMoves()
{
    std::vector<PathInstruction> instructions;

    instructions.push_back(PathInstruction(getForwardVector(), 1, false));

    Piece::calculatePossibleMoves(instructions);
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
