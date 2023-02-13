#ifndef STATUS_TYPES_H
#define STATUS_TYPES_H

#include <vector>
#include <string>
#include "MicroBitImage.h"

namespace StatusSystem
{

enum ETimingPolicy
{
    TP_Instant,
    TP_Duration,
    TP_Infinite
};

enum Operation
{
    Add,
    Multiply,
    Divide,
    Override
};

struct FAttribute
{
    FAttribute()
    {
        baseValue = value;
    }

    FAttribute(std::string _name, uint8_t _value)
        : name(_name)
        , value(_value)
        , baseValue(_value)
    {}

    std::string name;
    uint8_t value;
    uint8_t baseValue;
};

struct FModifier
{
    FModifier(std::string name, uint8_t mag, Operation op)
        : attributeName(name)
        , magnitude(mag)
        , operation(op)
    {}
    
    bool operator==(const FModifier& other)
    {
        return other.attributeName == attributeName;
    }

    std::string attributeName;
    uint8_t magnitude;
    Operation operation;
};

class StatusEffect
{
public:
    StatusEffect() {}

    std::vector<FModifier> modifiers;
    ETimingPolicy timingPolicy;
    uint8_t duration;
    MicroBitImage icon;
};

class SE_Rage : public StatusEffect
{
public:
    SE_Rage() 
    {
        modifiers.push_back(FModifier("health", 2, Divide));
        modifiers.push_back(FModifier("attack", 2, Add));

        timingPolicy = ETimingPolicy::TP_Duration;
        duration = 1;

        icon = MicroBitImage("\
                         0  255  0   0   0 \n\
                        255  0  255  0   0 \n\
                         0  255 255 255  0 \n\
                         0  255 255  0  255\n\
                        255 255 255 255 255\
        \n");
    }
};

class SE_Damage : public StatusEffect
{
public:
    SE_Damage(uint8_t amount)
    {
        modifiers.push_back(FModifier("health", -amount, Add));
        timingPolicy = ETimingPolicy::TP_Instant;
    }
};

}

#endif