#include "cursor.h"
#include "scene.h"
#include "fmath.h"
#include "pieces/pawn.h"
#include "pieces/rook.h"
#include "pieces/knight.h"
#include "status_system/status_types.h"

#include "player.h"

int main()
{
    Scene* scene = new Scene();
    Cursor* cursor = scene->spawnObject<Cursor>(Point(2, 2));
    scene->setCursor(cursor);
    // scene->getUBit()->display.setBrightness(64);

    Player* P1 = scene->createPlayer(ESide::Pins);
    Player* P2 = scene->createPlayer(ESide::Port);

    cursor->setCurrentPlayer(P1);

    // Player* P1 = new Player(scene, ESide::Pins);
    // Player* P2 = new Player(scene, ESide::Port);

    Pawn* test_subject = scene->grantPlayerPiece<Pawn>(Point(1, 0), P2);
    scene->grantPlayerPiece<Pawn>(Point(2, 0), P2);
    scene->grantPlayerPiece<Rook>(Point(3, 0), P2);

    scene->grantPlayerPiece<Knight>(Point(1, 2), P1);
    scene->grantPlayerPiece<Rook>(Point(1, 4), P1);
    scene->grantPlayerPiece<Pawn>(Point(2, 4), P1);
    scene->grantPlayerPiece<Rook>(Point(3, 4), P1);

    // StatusSystem::SE_Damage damage(3);
    // test_subject->ApplyStatusEffectToSelf(&damage);

    bool gaming = true;

    while(gaming)
    {
        scene->tick();
        scene->updateScene();
        scene->getUBit()->sleep(scene->sceneSpeed);
    }

    delete scene;
}