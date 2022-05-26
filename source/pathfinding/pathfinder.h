#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <vector>
#include "path_instruction.h"

class Pathfinder
{
public:
    Pathfinder(/* args */);
    ~Pathfinder();

    static std::vector<Point> calculateDestinations(class Scene* scene, class Piece* target, const std::vector<PathInstruction>& pathInstructions);

private:
};




#endif