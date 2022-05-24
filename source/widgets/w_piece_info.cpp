#include "w_piece_info.h"

#include "MicroBitImage.h"
#include "../cursor.h"
#include "../scene.h"
#include "../piece.h"

WPieceInfo::WPieceInfo()
{
}

MicroBitImage WPieceInfo::draw()
{
    MicroBitImage image(5, 5);

    if(inspectedPiece)
    {
        if(page == EPage::Owner)
        {
            if(inspectedPiece->getOwner() == scene->getCursor()->getCurrentPlayer())
            {
                MicroBitImage ownerIndicator("\
                                         0   0  255  0   0 \n\
                                         0   0  255  0   0 \n\
                                        255  0  255  0  255\n\
                                         0  255 255 255  0 \n\
                                         0   0  255  0   0 \n");

                image.paste(ownerIndicator, 0, 0);
            }
            else
            {
                MicroBitImage ownerIndicator("\
                                         0   0  255  0   0 \n\
                                         0  255 255 255  0 \n\
                                        255  0  255  0  255\n\
                                         0   0  255  0   0 \n\
                                         0   0  255  0   0 \n");

                image.paste(ownerIndicator, 0, 0);
            }
        }
        else if(page == EPage::Rank)
        {
            MicroBitImage classImage = inspectedPiece->classImage();
            image.paste(classImage, 0, 0);
        }
        else if(page == EPage::PowerInfo)
        {
            // display power (health and attack)
            for (uint8_t i = 0; i < inspectedPiece->getMaxHealth(); ++i)
            {
                uint8_t opacity = i < inspectedPiece->getHealth() ? 64 : 1;
                image.setPixelValue(i % 5, 0 + (uint8_t)(i / 5), opacity);
            }

            for (uint8_t i = 0; i < inspectedPiece->getMaxAttack(); ++i)
            {
                uint8_t opacity = i < inspectedPiece->getAttack() ? 64 : 1;
                image.setPixelValue(i % 5, 3 + (uint8_t)(i / 5), opacity);
            }
        }
    }

    return image;
}

void WPieceInfo::init(Piece* inspectedPiece)
{
    page = EPage::Owner;
    this->inspectedPiece = inspectedPiece;
}

void WPieceInfo::onSelect()
{
    page++;
}

void WPieceInfo::onBack()
{
    if(page == EPage::Owner)
        scene->removeWidget();
    else
        page--;
}
