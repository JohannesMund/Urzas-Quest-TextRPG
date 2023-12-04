#include "cdarkmobi.h"
#include "cgamemanagement.h"
#include "citemfactory.h"
#include "console.h"
#include "moduleressources.h"
#include "randomizer.h"
#include "ressources.h"

CDarkMobi::CDarkMobi()
{
    _name = Ressources::Game::mobi();
    _weapon = "poisonous tongue";
    _extendedWeaponChoice = true;

    _level = CGameManagement::getPlayerInstance()->level() + 2;
    _hp = 3 + (_level * 3);
}

void CDarkMobi::spoilsOfWar() const
{
    CGameManagement::getPlayerInstance()->addXp(_level * 1000);
}

void CDarkMobi::battleAction(bool& endRound)
{
    if (Randomizer::getRandom(3) == 0)
    {
        Console::printLn("Cut your live into pieces!");
        CGameManagement::getPlayerInstance()->dealDamage(2);
        endRound = true;
    }
    CEnemy::battleAction(endRound);
}

void CDarkMobi::postBattle()
{
}
