#ifndef W_PIECE_INFO_H
#define W_PIECE_INFO_H

#include "widget.h"
#include <type_traits>

enum EPage
{
    Owner,
    Rank,
    PowerInfo,
    StatusEffects,
    MAX
};

inline EPage& operator++(EPage& Other)
{
    using IntType = typename std::underlying_type<EPage>::type;
    Other = static_cast<EPage>(static_cast<IntType>(Other) + 1);
    if(Other == EPage::MAX)
        Other = static_cast<EPage>(0);

    return Other;
}

inline EPage& operator--(EPage& Other)
{
    if(Other == EPage::Owner)
        return Other;

    using IntType = typename std::underlying_type<EPage>::type;
    Other = static_cast<EPage>(static_cast<IntType>(Other) - 1);
    if(Other == EPage::MAX)
        Other = static_cast<EPage>(0);

    return Other;
}

inline EPage operator++(EPage& Other, int)
{
    const EPage Result = Other;
    ++Other;
    return Result;
}

inline EPage operator--(EPage& Other, int)
{
    const EPage Result = Other;
    --Other;
    return Result;
}

class Piece;

class WPieceInfo : public Widget
{
public:
    WPieceInfo(/* args */);

    virtual MicroBitImage draw() override;
    virtual void onSelect() override;
    virtual void onBack() override;
    void init(Piece* inspectedPiece);

private:
    Piece* inspectedPiece = nullptr;

    EPage page;
};

#endif