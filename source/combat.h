#ifndef COMBAT_H
#define COMBAT_H

#include "types/combat_types.h"

class Piece;

class Combat
{
public:
    Combat(Piece* _attacker, Piece* _defender);

    ECombatResult processCombat();

private:
    Piece* attacker;
    Piece* defender;

};

#endif