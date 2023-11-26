#include "cgoblinhorde.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "console.h"
#include "randomizer.h"

#include <format>

CGoblinHorde::CGoblinHorde() : CEnemyHorde(25, 3, 7)
{
    _level = std::max(1U, CGameManagement::getPlayerInstance()->level() - 2);
    _name = std::format("{}G{}reenskin{}", CC::fgGreen(), CC::fgLightGreen(), CC::ccReset());
    _weapon = "sticks, rocks and sharp teeth";
}

void CGoblinHorde::spoilsOfWar() const
{
    for (int i = 0; i < _count; i++)
    {
        CGameManagement::getPlayerInstance()->addXp(basicXP(_level));
    }

    Console::printLn("As expected, not much can be gained from them.");
    for (int i = 0; i < _count; i++)
    {
        if (Randomizer::getRandom(3) < 2)
        {
            do
            {
                CGameManagement::getInventoryInstance()->addLootItem();
            } while (Randomizer::getRandom(2) == 0);
        }
    }
}
