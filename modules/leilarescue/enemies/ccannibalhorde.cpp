#include "ccannibalhorde.h"
#include "../../rebellionhideout/cbagofingredients.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "console.h"
#include "randomizer.h"

#include <format>

CCannibalHorde::CCannibalHorde() : CEnemyHorde(25)
{
    _level = std::max(1U, CGameManagement::getPlayerInstance()->level() - 2);
    _name = std::format("C{}a{}nnibal{}", CC::fgYellow(), CC::fgWhite(), CC::ccReset());
    _weapon = "Kitchen knives";
}

void CCannibalHorde::spoilsOfWar() const
{
    for (auto i = 0U; i < _count; i++)
    {
        CGameManagement::getPlayerInstance()->addXp(basicXP(_level));
    }

    Console::printLn("The guys know one thing, food.");
    for (auto i = 0U; i < _count; i++)
    {
        if (Randomizer::getRandom(3) < 2)
        {
            do
            {
                CGameManagement::getInventoryInstance()->addItem(CBagOfIngredients::makeLootItem());
            } while (Randomizer::getRandom(2) == 0);
        }
    }
    Console::printLn("You probably don't want to know the whereabouts of some of the food items, but all this stuff "
                     "will make some great sandwiches.");
}

void CCannibalHorde::postBattle()
{
    CGameManagement::getProgressionInstance()->increaseGenocideCount();
}
