#include "combat.h"

#include "piece.h"

Combat::Combat(Piece* _attacker, Piece* _defender)
{
    attacker = _attacker;
    defender = _defender;
}

ECombatResult Combat::processCombat()
{
    attacker->dealDamage(defender);
    defender->dealDamage(attacker);

    if(attacker->getHealth() > 0 && defender->getHealth() > 0)
        return ECombatResult::Tie;

    if(attacker->getHealth() > 0 && defender->getHealth() <= 0)
    {
        defender->destroy();
        return ECombatResult::AttackerWins;
    }

    if(attacker->getHealth() <= 0 && defender->getHealth() > 0)
    {
        attacker->destroy();
        return ECombatResult::DefenderWins;
    }

    if(attacker->getHealth() <= 0 && defender->getHealth() <= 0)
    {
        attacker->destroy();
        defender->destroy();
        return ECombatResult::BothLose;
    }
}
