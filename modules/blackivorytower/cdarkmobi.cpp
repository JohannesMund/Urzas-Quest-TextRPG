#include "cdarkmobi.h"
#include "cgamemanagement.h"
#include "citemfactory.h"
#include "console.h"
#include "moduleressources.h"
#include "randomizer.h"
#include "ressources.h"

CDarkMobi::CDarkMobi(const bool isDeadly) : _isDeadly(isDeadly)
{
    _name = Ressources::Game::darkMobi();
    _weapon = tr("poisonous tongue");
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
        Console::printLn(tr("Cut your live into pieces!"));
        CGameManagement::getPlayerInstance()->dealDamage(2);
        endRound = true;
    }
    CEnemy::battleAction(endRound);
}

void CDarkMobi::postBattle()
{
    if (!_isDeadly)
    {
        if (CGameManagement::getPlayerInstance()->isDead())
        {
            Console::printLn(tr("{} laughes at you, while you are winding yourself in the dust below her feet, but "
                                "eventuallay, she helps you up.",
                                _name));
        }
        else
        {
            Console::printLn(tr("The Battle is over {} and you heal your wounds and go for a drink.", _name));
        }

        CGameManagement::getPlayerInstance()->fullHeal();
    }
}

std::string CDarkMobi::translatorModuleName() const
{
    return BlackIvoryTower::moduleName();
}
