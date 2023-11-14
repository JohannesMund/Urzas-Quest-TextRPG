#include "ccavebattleencounter.h"
#include "cbattle.h"
#include "cencounter.h"
#include "cmobenemy.h"
#include "moduleressources.h"

CCaveBattleEncounter::CCaveBattleEncounter()
{
    _type = CEncounter::eDungeon;
}

void CCaveBattleEncounter::execute(const std::string_view& moduleName)
{
    CEncounter::execute(moduleName);

    CMobEnemy enemy;
    enemy.setWeapon(CaveRessources::getRandomEnemyWeapon());
    enemy.setName(CaveRessources::getRandomEnemyName());

    CBattle battle(&enemy);
    battle.fight();
}

unsigned int CCaveBattleEncounter::encounterChance(const EEncounterType& tp, const std::string_view& moduleName) const
{
    if (moduleName.compare(CaveRessources::getEncounterName()) != 0)
    {
        return 0;
    }
    return CaveRessources::fightChance;
}

std::string CCaveBattleEncounter::name() const
{
    return "Battle";
}

std::string CCaveBattleEncounter::moduleName() const
{
    return CaveRessources::moduleName();
}
