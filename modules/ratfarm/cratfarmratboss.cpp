#include "cratfarmratboss.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "console.h"
#include "cratfarmturnip.h"
#include "moduleressources.h"
#include "randomizer.h"

#include <format>

CRatFarmRatBoss::CRatFarmRatBoss()
{
    _name = RatFarmRessources::getColoredBossString();

    _weapon = std::format("{}Still teeth, but yellow{}", CC::fgYellow(), CC::ccReset());
    _extendedWeaponChoice = true;

    _level = CGameManagement::getPlayerInstance()->level() + 2;
    _hp = 3 + (_level * 3);
}

void CRatFarmRatBoss::battleAction(bool& endRound)
{
    if (Randomizer::getRandom(3) == 0)
    {
        Console::printLn("You get hit by the tail.");
        CGameManagement::getPlayerInstance()->dealDamage(1);
        endRound = true;
    }
    CEnemy::battleAction(endRound);
}

void CRatFarmRatBoss::spoilsOfWar() const
{
    CGameManagement::getPlayerInstance()->addXp(CEnemy::basicXP(_level) * 3);
    Console::printLn("You will be surprised, what you find!");
    RatFarmRessources::TurnipFactory::addTurnips(Randomizer::getRandom(5) + 5);
}
