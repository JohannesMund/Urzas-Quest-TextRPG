#include "clivingchest.h"
#include "cgamemanagement.h"
#include "console.h"
#include "randomizer.h"

#include <algorithm>
#include <format>

CLivingChest::CLivingChest()
{
    _name = "Living Chest";
    _weapon = "Lick 'a tongue";
    _extendedWeaponChoice = true;

    _level = CGameManagement::getPlayerInstance()->level() + 1;
    _hp = 3 + (_level * Randomizer::getRandom(3));
}

void CLivingChest::spoilsOfWar() const
{
    CGameManagement::getPlayerInstance()->addXp(CEnemy::basicXP(_level));
}

void CLivingChest::battleAction(bool&)
{
    if (Randomizer::getRandom(std::max(10 - _level, 2U)) == 0)
    {
        Console::printLn(std::format("The {} of {} is totally unpredictable.", _weapon, _name));

        unsigned int amount = std::ceil(_level / 2);
        CGameManagement::getPlayerInstance()->dealDamage(amount);
    }
}
