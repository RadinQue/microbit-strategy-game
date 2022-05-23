#include "cursor.h"
#include "scene.h"
#include "fmath.h"
#include "pieces/pawn.h"

#include "player.h"

int main()
{
    Scene* scene = new Scene();
    Cursor* cursor = scene->spawnObject<Cursor>(Point(2, 2));

    Player* P1 = new Player();
    Player* P2 = new Player();

    cursor->setCurrentPlayer(P2);

    scene->grantPlayerPiece<Pawn>(Point(1, 0), P1);
    scene->grantPlayerPiece<Pawn>(Point(2, 0), P1);
    scene->grantPlayerPiece<Pawn>(Point(3, 0), P1);

    scene->grantPlayerPiece<Pawn>(Point(0, 4), P2);
    scene->grantPlayerPiece<Pawn>(Point(1, 4), P2);
    scene->grantPlayerPiece<Pawn>(Point(2, 4), P2);
    scene->grantPlayerPiece<Pawn>(Point(3, 4), P2);

    bool gaming = true;

    while(gaming)
    {
        scene->tick();
        scene->updateScene();
        scene->getUBit()->sleep(scene->sceneSpeed);
    }

    delete scene;
}