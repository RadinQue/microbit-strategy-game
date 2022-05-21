#include "u_bit_instance.h"
#include "player.h"

#define MOVEMENT_THRESHOLD 20

int main()
{
    uBit.init();

    Player* my_player = new Player(0, 0);

    bool gaming = true;

    while(gaming)
    {
        uBit.display.clear();

        bool direction = true;
        bool moving = true;

        int x_tilt = uBit.accelerometer.getX();
        int y_tilt = uBit.accelerometer.getY();

        int roll = uBit.accelerometer.getRoll();
        int pitch = uBit.accelerometer.getPitch();

        if(roll < -MOVEMENT_THRESHOLD)
            direction = true;
        else if(roll > MOVEMENT_THRESHOLD)
            direction = false;
        else
            moving = false;

        Point offset_direction(1, 0);
        if(direction)
            offset_direction = offset_direction * -1;

        if(moving)
            my_player->offset(offset_direction);

        uBit.display.image.setPixelValue(my_player->get_location().x, my_player->get_location().y, 255);

        uBit.sleep(500);
    }
    
    release_fiber();
}
