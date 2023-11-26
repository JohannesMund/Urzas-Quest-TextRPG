#include "clayla2goblinencounter.h"
#include "cgamemanagement.h"
#include "claylasribbon.h"
#include "colorize.h"
#include "console.h"
#include "layla2/moduleressources.h"
#include "layla2/tasks/clayla2goblinvillagetask.h"
#include "ressources.h"

#include <format>

CLayla2GoblinEncounter::CLayla2GoblinEncounter()
{
    _isSingleExecution = true;
    _type = CEncounter::eField;
}

void CLayla2GoblinEncounter::execute(const std::string_view& moduleName)
{
    Console::printLn(
        std::format("Backtracking {}s way since you first rescued her, you have seen a lot of the land, but not the "
                    "{}. {} is all bitchy again towards you and you start asking yourself, if all this is really worth "
                    "it, until all of a sudden, a {}colorfull {}accent{} can be seen in one of the bushes.",
                    Ressources::Game::layla(),
                    Layla2Ressources::ribbon(),
                    Ressources::Game::princessLayla(),
                    CC::fgMagenta(),
                    CC::fgLightMagenta(),
                    CC::ccReset()));
    Console::printLn(std::format("Finally, you found {}s {}, and before you can ask her to stay cautious, because that "
                                 "might be a trap, she runs towards her treasure, and... well... it was a trap.",
                                 Ressources::Game::princessLayla(),
                                 Layla2Ressources::ribbon()));
    Console::br();
    Console::printLn(
        std::format("{} gets hit by a club and is drawn into the woods. You run towards her, but all you can see is "
                    "some {}, running away on a wild boar, with the lady of your over his shoulders.",
                    Ressources::Game::princessLayla(),
                    Layla2Ressources::greenskin()));
    Console::printLn(std::format("At least you are able to recover her {}. You pick it up and put it in your pocket. "
                                 "Maybe this will make you her hero, when you give it back to her.",
                                 Layla2Ressources::ribbon()));
    Console::printLn("You will have to find him and burn down his house, his family, his children and his whole "
                     "village. It's a beautiful day for a genocide.");
    Console::br();
    CGameManagement::getInventoryInstance()->addItem(new CLaylasRibbon());
    CGameManagement::getInstance()->placeTaskOnField(new CLayla2GoblinVillageTask());
    _hasBeenExecuted = true;
}

unsigned int CLayla2GoblinEncounter::encounterChance(const EEncounterType& tp, const std::string_view& moduleName) const
{
    return 5;
}

std::string CLayla2GoblinEncounter::name() const
{
    return std::format("{}s {}", Ressources::Game::princessLayla(), Layla2Ressources::ribbon());
}

std::string CLayla2GoblinEncounter::moduleName() const
{
    return Layla2Ressources::encounterNameFindRibbon();
}
