#include "cgoblinhorde.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "console.h"
#include "leila2/moduleressources.h"
#include "randomizer.h"

#include <format>

CGoblinHorde::CGoblinHorde() : CEnemyHorde(25)
{
    _name = tr("{}G{}reenskin{}", CC::fgGreen(), CC::fgLightGreen(), CC::ccReset());
    _weapon = tr("sticks, rocks and sharp teeth");
}

void CGoblinHorde::spoilsOfWar() const
{
    for (auto i = 0U; i < _count; i++)
    {
        CGameManagement::getPlayerInstance()->addXp(basicXP(_level));
    }

    Console::printLn(tr("As expected, not much can be gained from them."));
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

void CGoblinHorde::postBattle()
{
    CGameManagement::getProgressionInstance()->increaseGenocideCount();
}

std::string CGoblinHorde::translatorModuleName() const
{
    return Leila2::moduleName();
}
