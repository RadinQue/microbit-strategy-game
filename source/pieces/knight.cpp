#include "knight.h"
#include "pathfinding/path_instruction.h"
#include "MicroBitImage.h"


//remove
#include "scene.h"

Knight::Knight(const Point& location, Scene* scene)
{
    this->scene = scene;
    this->location = location;

    maxHealth.value = 4;
    maxAttack.value = 3;
}

void Knight::calculatePossibleMoves()
{
    std::vector<PathInstruction> instructions;

    instructions.push_back(PathInstruction(getForwardVector() * 2 + getRightVector(), 1, true));
    instructions.push_back(PathInstruction(getForwardVector() * 2 + getRightVector() * -1, 1, true));
    instructions.push_back(PathInstruction(getForwardVector() * -2 + getRightVector() * -1, 1, true));
    instructions.push_back(PathInstruction(getForwardVector() * -2 + getRightVector(), 1, true));

    instructions.push_back(PathInstruction(getRightVector() * 2 + getForwardVector(), 1, true));
    instructions.push_back(PathInstruction(getRightVector() * 2 + getForwardVector() * -1, 1, true));
    instructions.push_back(PathInstruction(getRightVector() * -2 + getForwardVector() * -1, 1, true));
    instructions.push_back(PathInstruction(getRightVector() * -2 + getForwardVector(), 1, true));

    Piece::calculatePossibleMoves(instructions);
}

MicroBitImage Knight::classImage()
{
    MicroBitImage image("\
                     0   0  255  0   0 \n\
                     0   0  255  0   0 \n\
                     0   0  255  0   0 \n\
                     0  255 255 255  0 \n\
                     0   0  255  0   0 \n");

    return image;
}
