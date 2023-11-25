#include "csewerboss.h"
#include "cgamemanagement.h"
#include "citemfactory.h"
#include "console.h"
#include "moduleressources.h"
#include "randomizer.h"

CSewerBoss::CSewerBoss()
{
    _name = SewerRessources::getColoredBossString();
    _weapon = SewerRessources::getBossWeapon();
    _extendedWeaponChoice = true;

    _level = CGameManagement::getPlayerInstance()->level() + 2;
    _hp = 3 + (_level * 3);
}

void CSewerBoss::spoilsOfWar() const
{
    CGameManagement::getPlayerInstance()->addXp(_level * 200);
    Console::printLn("It is a cockroach, but is has money.");
    CGameManagement::getPlayerInstance()->gainGold(Randomizer::getRandom(_level * 100) + _level * 33);

    Console::printLn("Going through his bag, you find some more or less usefull items.");
    auto amount = Randomizer::getRandom(3) + 1;
    for (auto i = 0; i <= amount; i++)
    {
        CGameManagement::getInventoryInstance()->addShopItem();
    }

    amount = Randomizer::getRandom(7) + 5;
    for (auto i = 0; i <= amount; i++)
    {
        CGameManagement::getInventoryInstance()->addLootItem();
    }

    CGameManagement::getInventoryInstance()->addShopItem();
}

void CSewerBoss::battleAction(bool& endRound)
{
    if (Randomizer::getRandom(3) == 0)
    {
        Console::printLn("Cut your live into pieces!");
        CGameManagement::getPlayerInstance()->dealDamage(2);
        endRound = true;
    }
    CEnemy::battleAction(endRound);
}
