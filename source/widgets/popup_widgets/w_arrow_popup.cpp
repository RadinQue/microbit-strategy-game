#include "w_arrow_popup.h"
#include "MicroBitImage.h"
#include "../../player.h"

MicroBitImage WArrowPopup::draw()
{
    return MicroBitImage ("\
        0   0  255  0   0 \n\
        0   0  255  0   0 \n\
        255  0  255  0  255\n\
        0  255 255 255  0 \n\
        0   0  255  0   0 \n");
}