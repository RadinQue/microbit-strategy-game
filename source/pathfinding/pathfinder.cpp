#include "pathfinder.h"
#include "../scene.h"
#include "../piece.h"
#include "../cursor.h"

Pathfinder::Pathfinder(/* args */)
{
}

Pathfinder::~Pathfinder()
{
}

std::vector<Point> Pathfinder::calculateDestinations(Scene* scene, Piece* target, const std::vector<PathInstruction>& pathInstructions)
{
    std::vector<Point> points;

    if(!scene || !target)
        return points;

    FCastQuery castQuery;
    castQuery.filteredObjects.push_back(scene->getCursor());

    for (const PathInstruction& instruction : pathInstructions)
    {
        uint8_t range = instruction.range == -1 ? 4 : instruction.range;

        for (uint8_t i = 0; i < range; ++i)
        {
            if(scene->isOutOfBounds(target->getLocation() + instruction.direction * (i + 1)))
                break;

            Point checkLocation = Point(target->getLocation() + instruction.direction * (i + 1));
            if(!scene->spaceOccupied(checkLocation, castQuery))
            {
                // nothing on this location, add it to the destinations and
                // continue discovering the path
                points.push_back(checkLocation);
                continue;
            }

            // there's a piece on this location
            if(Piece* pieceAtLocation = static_cast<Piece*>(scene->getObjectAtLocationOfType(checkLocation, EMessageType::EMT_Piece, castQuery)))
            {
                // see if it belongs to the opponent
                if(pieceAtLocation->getOwner() != target->getOwner())
                    points.push_back(checkLocation); // if so, it's still a valid move

                // but then if can't pass through,
                // break out of this path
                if(!instruction.bPassThrough)
                    break;
            }
        }
    }

    return points;
}
