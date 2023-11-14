#include "clakeoftearsboss.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "console.h"
#include "moduleressources.h"
#include "randomizer.h"

#include <format>

CLakeOfTearsBoss::CLakeOfTearsBoss() : CTwoEnemies(LakeTearsRessources::bimmelchen(), LakeTearsRessources::pimmelchen())
{
    _name = "";
    _weapon = "Crocodile Tears of Despair";
    _extendedWeaponChoice = true;

    _level = CGameManagement::getPlayerInstance()->level() + 2;
    _hp1 = Randomizer::getRandom(5) + 1 + (_level * Randomizer::getRandom(2) + 3);
    _hp2 = Randomizer::getRandom(2) + 3 + (_level * Randomizer::getRandom(4) + 1);
    _hp = _hp1 + _hp2;
}

void CLakeOfTearsBoss::spoilsOfWar() const
{
    CGameManagement::getPlayerInstance()->addXp(_level * 400);
    CGameManagement::getPlayerInstance()->addXp(_level * 400);
    Console::printLn("As expected they have nothing. You feel sad, dirty and just want to go.");
}

void CLakeOfTearsBoss::passiveBattleAction(EWho who)
{

    auto dmg = Randomizer::getRandom(3);
    if (dmg > 0)
    {
        if (who == CTwoEnemies::EWho::eEnemy1)
        {
            Console::printLn(std::format("{} attacks you", LakeTearsRessources::bimmelchen()));
        }
        else
        {
            Console::printLn(std::format("{} attacks you", LakeTearsRessources::pimmelchen()));
        }

        CGameManagement::getPlayerInstance()->dealDamage(dmg);
    }
}
