#include "ccaveboss.h"
#include "cgamemanagement.h"
#include "console.h"
#include "itemfactory.h"
#include "moduleressources.h"
#include "randomizer.h"

CCaveBoss::CCaveBoss() : CEnemy()
{
    _name = CaveRessources::getColoredBossString();
    _weapon = CaveRessources::getBossWeapon();
    _extendedWeaponChoice = true;

    _level = CGameManagement::getPlayerInstance()->level() + 2;
    _hp = 3 + (_level * 3);
}

void CCaveBoss::spoilsOfWar() const
{
    CGameManagement::getPlayerInstance()->addXp(_level * 200);
    Console::printLn("For such an ugly, savage beeing, this guy has quite some money.");
    CGameManagement::getPlayerInstance()->addGold(Randomizer::getRandom(_level * 100) + _level * 33);

    Console::printLn("Going through his bag, you find some more or less usefull items.");
    auto amount = Randomizer::getRandom(3) + 1;
    for (auto i = 0; i <= amount; i++)
    {
        CGameManagement::getInventoryInstance()->addItem(ItemFactory::makeShopItem());
    }

    amount = Randomizer::getRandom(7) + 5;
    for (auto i = 0; i <= amount; i++)
    {
        CGameManagement::getInventoryInstance()->addItem(ItemFactory::makeLootItem());
    }

    CGameManagement::getInventoryInstance()->addItem(ItemFactory::makeAwesomneItem());
}

void CCaveBoss::battleAction(bool& endRound)
{
    if (Randomizer::getRandom(3) == 0)
    {
        Console::printLn("You get hit with a mighty splash.");
        CGameManagement::getPlayerInstance()->dealDamage(2);
        endRound = true;
    }
    CEnemy::battleAction(endRound);
}
