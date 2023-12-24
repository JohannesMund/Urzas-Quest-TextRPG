#include "cmobenemy.h"
#include "cgamemanagement.h"
#include "console.h"
#include "randomizer.h"
#include "ressources.h"

#include <algorithm>

CMobEnemy::CMobEnemy() : CEnemy()
{
    _name = Ressources::Enemies::getRandomEnemyName();
    _weapon = Ressources::Enemies::getRandomEnemyWeapon();

    auto minLevel = std::max((int)(CGameManagement::getPlayerInstance()->level()) - 2, 1);
    auto maxLevel = CGameManagement::getPlayerInstance()->level() + 2;
    _level = Randomizer::getRandom(maxLevel - minLevel) + minLevel;
    _initiative = Randomizer::getRandom(3) + 1;

    _hp = basicHP(_level);

    if (_level >= 2)
    {
        _specialAttackChance = 10;
    }
    if (_level >= 3)
    {
        _initiative++;
    }
    if (_level >= 4)
    {
        _specialAttackChance = 8;
    }
    if (_level >= 5)
    {
        _extendedWeaponChoice = Randomizer::getRandom(2) == 0;

        _initiative += Randomizer::getRandom(5) + 1;
    }
    if (_level >= 6)
    {
        _specialAttackChance = 5;
    }
    if (_level >= 7)
    {
        _extendedWeaponChoice = true;
        _initiative++;
    }
    if (_level >= 10)
    {
        _specialAttackChance = 3;
    }
}

void CMobEnemy::battleAction(bool& endRound)
{
    if (_specialAttackChance > 0 && Randomizer::getRandom(_specialAttackChance) == 0)
    {
        specialAttack();
        endRound = true;
    }
    CEnemy::battleAction(endRound);
}

void CMobEnemy::setName(const std::string& name)
{
    _name = name;
}

void CMobEnemy::setWeapon(const std::string& weapon)
{
    _weapon = weapon;
}

void CMobEnemy::specialAttack()
{
    Console::printLn("Special Attack!");
    CGameManagement::getPlayerInstance()->dealDamage(1);
}
