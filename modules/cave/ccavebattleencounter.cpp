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
    enemy.setWeapon(Cave::getRandomEnemyWeapon());
    enemy.setName(Cave::getRandomEnemyName());

    CBattle battle(&enemy);
    battle.fight();
}

unsigned int CCaveBattleEncounter::encounterChance(const EEncounterType&, const std::string_view& moduleName) const
{
    if (moduleName.compare(Cave::moduleName()) != 0)
    {
        return 0;
    }
    return Cave::fightChance;
}

std::string CCaveBattleEncounter::name() const
{
    return "Battle";
}

std::string CCaveBattleEncounter::moduleName() const
{
    return Cave::dungeonEncounterName();
}

std::string CCaveBattleEncounter::translatorModuleName() const
{
    return Cave::moduleName();
}
