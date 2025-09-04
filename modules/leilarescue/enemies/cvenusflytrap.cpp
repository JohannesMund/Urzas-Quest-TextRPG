#include "cvenusflytrap.h"
#include "../moduleressources.h"
#include "cgamemanagement.h"
#include "citemfactory.h"
#include "console.h"
#include "randomizer.h"

CVenusFlyTrap::CVenusFlyTrap() : CEnemy()
{
    _name = LeilaRescueRessources::getColoredBossString();
    _weapon = LeilaRescueRessources::getBossWeapon();
    _extendedWeaponChoice = true;

    _level = CGameManagement::getPlayerInstance()->level() + 2;
    _hp = 3 + (_level * 3);
}

void CVenusFlyTrap::spoilsOfWar() const
{
    CGameManagement::getPlayerInstance()->addXp(_level * 200);
    Console::printLn("For such an ugly, savage beeing, this guy has quite some money.");
    CGameManagement::getPlayerInstance()->gainGold(Randomizer::getRandom(_level * 100) + _level * 33);

    Console::printLn("Going through his bag, you find some more or less usefull items.");
    auto amount = Randomizer::getRandom(3) + 1;
    for (auto i = 0U; i <= amount; i++)
    {
        CGameManagement::getInventoryInstance()->addShopItem();
    }

    amount = Randomizer::getRandom(7) + 5;
    for (auto i = 0U; i <= amount; i++)
    {
        CGameManagement::getInventoryInstance()->addLootItem();
    }

    CGameManagement::getInventoryInstance()->addAwesomneItem();
}

void CVenusFlyTrap::battleAction(bool& endRound)
{
    if (Randomizer::getRandom(3) == 0)
    {
        Console::printLn("You get hit with a mighty splash.");
        CGameManagement::getPlayerInstance()->dealDamage(2);
        endRound = true;
    }
    CEnemy::battleAction(endRound);
}
