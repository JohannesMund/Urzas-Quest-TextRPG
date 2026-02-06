#include "csewerbattleencounter.h"
#include "cbattle.h"
#include "cencounter.h"
#include "cmobenemy.h"
#include "moduleressources.h"

CSewerBattleEncounter::CSewerBattleEncounter()
{
    _type = CEncounter::eDungeon;
}

void CSewerBattleEncounter::execute(const std::string_view& moduleName)
{
    CEncounter::execute(moduleName);

    CMobEnemy enemy;
    enemy.setWeapon(Sewer::getRandomEnemyWeapon());
    enemy.setName(Sewer::getRandomEnemyName());

    CBattle battle(&enemy);
    battle.fight();
}

unsigned int CSewerBattleEncounter::encounterChance(const EEncounterType&, const std::string_view& moduleName) const
{
    if (moduleName.compare(Sewer::moduleName()) != 0)
    {
        return 0;
    }
    return Sewer::fightChance;
}

std::string CSewerBattleEncounter::name() const
{
    return "Battle";
}

std::string CSewerBattleEncounter::moduleName() const
{
    return Sewer::dungeonEncounterName();
}
