#include "pawn.h"
#include "pathfinding/path_instruction.h"
#include "MicroBitImage.h"


Pawn::Pawn(const Point& location, Scene* scene)
{
    this->scene = scene;
    this->location = location;

    maxHealth.value = 3;
    maxAttack.value = 2;
}

void Pawn::start()
{
    Piece::start();

    health = StatusSystem::FAttribute("health", 5);
    attack = StatusSystem::FAttribute("attack", 3);

    maxHealth = StatusSystem::FAttribute("max_health", 5);
    maxAttack = StatusSystem::FAttribute("max_attack", 3);
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
