#include "claylabossorks.h"
#include "cgamemanagement.h"
#include "console.h"
#include "layla2/moduleressources.h"
#include "randomizer.h"

#include <format>

CLaylaBossOrks::CLaylaBossOrks() : CTwoEnemies(Layla2Ressources::mork(), Layla2Ressources::gork())
{
    _name = "";
    _weapon = "Trunk and Rock";
    _extendedWeaponChoice = true;

    _level = CGameManagement::getPlayerInstance()->level() + 2;
    _hp1 = Randomizer::getRandom(5) + 1 + (_level * Randomizer::getRandom(2) + 3);
    _hp2 = Randomizer::getRandom(2) + 3 + (_level * Randomizer::getRandom(4) + 1);
    _hp = _hp1 + _hp2;
}

void CLaylaBossOrks::spoilsOfWar() const
{
    CGameManagement::getPlayerInstance()->addXp(_level * 400);

    Console::printLn("Those two collected quite a fortune.");

    CGameManagement::getPlayerInstance()->gainGold(Randomizer::getRandom(_level * 200) +
                                                   _level * (Randomizer::getRandom(65) + 1));
    auto amount = Randomizer::getRandom(4) + 7;
    for (auto i = 0U; i <= amount; i++)
    {
        CGameManagement::getInventoryInstance()->addLootItem();
    }
}

void CLaylaBossOrks::passiveBattleAction(EWho who)
{
    auto dmg = Randomizer::getRandom(3);
    if (dmg > 0)
    {
        if (who == CTwoEnemies::EWho::eEnemy1)
        {
            Console::printLn(std::format("{} attacks you", _name1));
        }
        else
        {
            Console::printLn(std::format("{} attacks you", _name2));
        }

        CGameManagement::getPlayerInstance()->dealDamage(dmg);
    }
}

std::string CLaylaBossOrks::name() const
{
    return std::format("{} and {} from {}Ork{}", _name1, _name2, CC::fgLightGreen(), CC::ccReset());
}
