#include "claylabossguards.h"
#include "cgamemanagement.h"
#include "console.h"
#include "layla2/moduleressources.h"
#include "randomizer.h"

#include <format>

CLaylaBossGuards::CLaylaBossGuards() : CTwoEnemies(Layla2Ressources::bimmel(), Layla2Ressources::bommel())
{
    _name = "";
    _weapon = "Sword and Pike";
    _extendedWeaponChoice = true;

    _level = CGameManagement::getPlayerInstance()->level() + 2;
    _hp1 = Randomizer::getRandom(5) + 1 + (_level * Randomizer::getRandom(2) + 3);
    _hp2 = Randomizer::getRandom(2) + 3 + (_level * Randomizer::getRandom(4) + 1);
    _hp = _hp1 + _hp2;
}

void CLaylaBossGuards::spoilsOfWar() const
{
    CGameManagement::getPlayerInstance()->addXp(_level * 400);
    CGameManagement::getPlayerInstance()->addXp(_level * 400);

    Console::printLn(std::format("{} and {} realize, that they will not stand a chance and run away", _name1, _name2));
    Console::printLn(std::format("\"{} will not like that!\" - \"{} Neither, but their punishment is better, than "
                                 "dealing with this monster!\"",
                                 Ressources::Game::fiego(),
                                 Ressources::Game::brock()));

    Console::printLn(std::format("Crime seems to be well paid.", CC::fgBlue(), CC::fgYellow(), CC::ccReset()));

    CGameManagement::getPlayerInstance()->gainGold(Randomizer::getRandom(_level * 100) +
                                                   _level * (Randomizer::getRandom(65) + 1));
    CGameManagement::getPlayerInstance()->gainGold(Randomizer::getRandom(_level * 100) +
                                                   _level * (Randomizer::getRandom(65) + 1));
    auto amount = Randomizer::getRandom(4) + 7;
    for (auto i = 0; i <= amount; i++)
    {
        CGameManagement::getInventoryInstance()->addLootItem();
    }
}

void CLaylaBossGuards::passiveBattleAction(EWho who)
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
