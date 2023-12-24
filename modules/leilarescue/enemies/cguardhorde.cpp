#include "cguardhorde.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "console.h"
#include "randomizer.h"

#include <format>

CGuardHorde::CGuardHorde() : CEnemyHorde(15)
{
    _level = std::max(1U, CGameManagement::getPlayerInstance()->level() - 2);
    _name = std::format("{}Prison {}Guards{}", CC::fgRed(), CC::fgCyan(), CC::ccReset());
    _weapon = "sticks, rocks and sharp teeth";
}

void CGuardHorde::spoilsOfWar() const
{
    for (auto i = 0U; i < _count; i++)
    {
        CGameManagement::getPlayerInstance()->addXp(basicXP(_level));
    }

    Console::printLn("As expected, not much can be gained from them.");
    for (auto i = 0U; i < _count; i++)
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
