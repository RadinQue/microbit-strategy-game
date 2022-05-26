#ifndef STATUS_TYPES_H
#define STATUS_TYPES_H

#include <vector>
#include "MicroBitImage.h"

class StatusEffect
{
public:
    StatusEffect() {}

    std::vector<FModifier> modifiers;
    ETimingPolicy timingPolicy;
    MicroBitImage icon;
};

struct FModifier
{
    FAttribute attribute;
    int magnitude;
};

struct FAttribute
{
    char* name;
    int value;
};

enum ETimingPolicy
{
    TP_Instant,
    TP_Duration,
    TP_Infinite
};

#endif