#include "cratfarmrat.h"
#include "cgamemanagement.h"
#include "cratfarmturnip.h"
#include "moduleressources.h"
#include "randomizer.h"

CRatFarmRat::CRatFarmRat()
{

    _name = "Rat";
    _weapon = "Teeth";

    _level = CGameManagement::getPlayerInstance()->level();
    _initiative = 5;

    _hp = 3;

    if (_level >= 2)
    {
        _hp++;
    }
    if (_level >= 3)
    {

        _initiative++;
    }
    if (_level >= 4)
    {
        _hp++;
    }
    if (_level >= 5)
    {
        _extendedWeaponChoice = true;
        _hp += 3;
        _initiative += 5;
    }
    if (_level >= 10)
    {
        _hp += 10;
        _initiative += 10;
    }
}

void CRatFarmRat::battleAction(bool&)
{
}

void CRatFarmRat::spoilsOfWar() const
{
    CGameManagement::getPlayerInstance()->addXp(CEnemy::basicXP(_level));
    RatFarmRessources::TurnipFactory::addTurnips(Randomizer::getRandom(2));
}
