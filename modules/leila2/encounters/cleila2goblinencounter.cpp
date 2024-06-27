#include "cleila2goblinencounter.h"
#include "cgamemanagement.h"
#include "claylasribbon.h"
#include "colorize.h"
#include "console.h"
#include "leila2/moduleressources.h"
#include "leila2/tasks/cleila2goblinvillagetask.h"
#include "ressources.h"

#include <format>

CLeila2GoblinEncounter::CLeila2GoblinEncounter()
{
    _isSingleExecution = true;
    _type = CEncounter::eField;
}

void CLeila2GoblinEncounter::execute(const std::string_view&)
{
    Console::printLn(
        std::format("Backtracking {}s way since you first rescued her, you have seen a lot of the land, but not the "
                    "{}. {} is all bitchy again towards you and you start asking yourself, if all this is really worth "
                    "it, until all of a sudden, a {}colorfull {}accent{} can be seen in one of the bushes.",
                    Ressources::Game::leila(),
                    Ressources::Game::leilasRibbon(),
                    Ressources::Game::princessLeila(),
                    CC::fgMagenta(),
                    CC::fgLightMagenta(),
                    CC::ccReset()));
    Console::printLn(std::format("Finally, you found {}s {}, and before you can ask her to stay cautious, because that "
                                 "might be a trap, she runs towards her treasure, and... well... it was a trap.",
                                 Ressources::Game::princessLeila(),
                                 Ressources::Game::leilasRibbon()));
    Console::br();
    Console::printLn(
        std::format("{} gets hit by a club and is drawn into the woods. You run towards her, but all you can see is "
                    "some {}, running away on a wild boar, with the lady of your over his shoulders.",
                    Ressources::Game::princessLeila(),
                    Leila2Ressources::greenskin()));
    Console::printLn(std::format("At least you are able to recover her {}. You pick it up and put it in your pocket. "
                                 "Maybe this will make you her hero, when you give it back to her.",
                                 Ressources::Game::leilasRibbon()));
    Console::printLn("You will have to find him and burn down his house, his family, his children and his whole "
                     "village. It's a beautiful day for a genocide.");
    Console::br();
    CGameManagement::getInventoryInstance()->addItem(new CLaylasRibbon());
    CGameManagement::getInstance()->placeTaskOnField(new CLeila2GoblinVillageTask());
    _hasBeenExecuted = true;
}

unsigned int CLeila2GoblinEncounter::encounterChance(const EEncounterType&, const std::string_view&) const
{
    return 5;
}

std::string CLeila2GoblinEncounter::name() const
{
    return std::format("{}s {}", Ressources::Game::princessLeila(), Ressources::Game::leilasRibbon());
}

std::string CLeila2GoblinEncounter::moduleName() const
{
    return Leila2Ressources::encounterNameFindRibbon();
}
