#include "cbattleencounter.h"
#include "cbattle.h"
#include "ressources.h"

CBattleEncounter::CBattleEncounter() : CEncounter()
{
    _type = CEncounter::eField;
}

void CBattleEncounter::execute(const std::string_view& moduleName)
{
    CEncounter::execute(moduleName);

    CBattle battle;
    battle.fight();
}

unsigned int CBattleEncounter::encounterChance(const EEncounterType&, const std::string_view&) const
{
    return Ressources::Config::fightChance;
}

std::string CBattleEncounter::name() const
{
    return "Battle";
}
