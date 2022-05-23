#include "cursor.h"
#include "scene.h"
#include "fmath.h"

#define MOVEMENT_THRESHOLD 20

int main()
{
    Scene* scene = new Scene();
    Cursor* cursor = scene->spawnObject<Cursor>(Point(2, 2));

    bool gaming = true;


    while(gaming)
    {
        scene->tick();
        scene->updateScene();
        scene->getUBit()->sleep(300);
    }

    delete scene;
}
