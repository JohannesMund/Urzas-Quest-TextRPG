#include "cnpcenemy.h"
#include "cgamemanagement.h"
#include "cnpc.h"
#include "console.h"

CNpcEnemy::CNpcEnemy(const CNpc* npc)
{
    _name = npc->name();
    _weapon = coreTr("training weapon");
    _extendedWeaponChoice = true;

    _level = CGameManagement::getPlayerInstance()->level();
    _hp = 3 + (_level * 3);
}

void CNpcEnemy::postBattle()
{
    Console::printLn(coreTr("The Battle is over {} and you heal your wounds and go for a drink.", _name));
    CGameManagement::getPlayerInstance()->fullHeal();
}

std::string CNpcEnemy::translatorModuleName() const
{
    return std::string();
}
