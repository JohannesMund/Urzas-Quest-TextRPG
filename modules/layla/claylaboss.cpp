#include "claylaboss.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "console.h"
#include "moduleressources.h"
#include "randomizer.h"

#include <format>

CLaylaBoss::CLaylaBoss() : CTwoEnemies(LaylaRessources::piefke(), LaylaRessources::schniefke())
{
    _name = "";
    _weapon = "Sword and Pike";
    _extendedWeaponChoice = true;

    _level = CGameManagement::getPlayerInstance()->level() + 2;
    _hp1 = Randomizer::getRandom(5) + 1 + (_level * Randomizer::getRandom(2) + 3);
    _hp2 = Randomizer::getRandom(2) + 3 + (_level * Randomizer::getRandom(4) + 1);
    _hp = _hp1 + _hp2;
}

void CLaylaBoss::spoilsOfWar() const
{
    CGameManagement::getPlayerInstance()->addXp(_level * 400);
    CGameManagement::getPlayerInstance()->addXp(_level * 400);

    Console::printLn(std::format("{} and {} realize, that they will not stand a chance and run away",
                                 LaylaRessources::piefke(),
                                 LaylaRessources::schniefke()));
    Console::printLn(std::format("\"{} will not like that!\" - \"{} Neither, but their punishment is better, than "
                                 "dealing with this monster!\"",
                                 Ressources::Game::fiego(),
                                 Ressources::Game::brock()));

    Console::printLn(std::format("Crime seems to be well paid.", CC::fgBlue(), CC::fgYellow(), CC::ccReset()));

    CGameManagement::getPlayerInstance()->addGold(Randomizer::getRandom(_level * 100) +
                                                  _level * (Randomizer::getRandom(65) + 1));
    CGameManagement::getPlayerInstance()->addGold(Randomizer::getRandom(_level * 100) +
                                                  _level * (Randomizer::getRandom(65) + 1));
    auto amount = Randomizer::getRandom(4) + 7;
    for (auto i = 0; i <= amount; i++)
    {
        CGameManagement::getInventoryInstance()->addItem(ItemFactory::makeItem(ItemFactory::EItemType::eJunkItem));
    }
}

void CLaylaBoss::passiveBattleAction(EWho who)
{
    auto dmg = Randomizer::getRandom(3);
    if (dmg > 0)
    {
        if (who == CTwoEnemies::EWho::eEnemy1)
        {
            Console::printLn(std::format("{} attacks you", LaylaRessources::piefke()));
        }
        else
        {
            Console::printLn(std::format("{} attacks you", LaylaRessources::schniefke()));
        }

        CGameManagement::getPlayerInstance()->dealDamage(dmg);
    }
}
