#include "w_piece_info.h"

#include "MicroBitImage.h"
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
        if(page == EPage::Rank)
        {
            MicroBitImage classImage = inspectedPiece->classImage();
            image.paste(classImage, 0, 0);
        }
        else if(page == EPage::PowerInfo)
        {
            for (uint8_t i = 0; i < 10; ++i)
            {
                uint8_t opacity = i < inspectedPiece->getHealth() ? 64 : 1;
                image.setPixelValue(i % 5, 0 + (uint8_t)(i / 5), opacity);
            }

            for (uint8_t i = 0; i < 10; ++i)
            {
                uint8_t opacity = i < inspectedPiece->getMagic() ? 64 : 1;
                image.setPixelValue(i % 5, 3 + (uint8_t)(i / 5), opacity);
            }
        }
    }

    return image;
}

void WPieceInfo::init(Piece* inspectedPiece)
{
    page = EPage::Rank;
    this->inspectedPiece = inspectedPiece;
}

void WPieceInfo::onSelect()
{
    page++;
}

void WPieceInfo::onBack()
{
    if(page == EPage::Rank)
        scene->removeWidget();
    else
        page--;
}
