#include "clakeoftearsencounter.h"
#include "cgamemanagement.h"
#include "clakeoftearstask.h"
#include "cmenu.h"
#include "colorconsole.h"
#include "console.h"
#include "moduleressources.h"
#include "ressources.h"

#include <format>
#include <string>

CLakeOfTearsEncounter::CLakeOfTearsEncounter()
{
    _isSingleExecution = true;
    _type = CEncounter::eField;
}

void CLakeOfTearsEncounter::execute(const std::string_view& moduleName)
{
    CEncounter::execute(moduleName);
    _hasBeenExecuted = true;

    Console::printLn("During your journey, you pass a tiny villag. Even though, you passed this region several times, "
                     "you never took notice of this particular village. Maybe because it is just too small.");
    Console::printLn("The villagers look poor, sick and weak. A very old, shaky man asks you for some water. You feel "
                     "pittry for and give him your bottle.");
    Console::printLn(
        std::format("\"Back than, before the war, {0} would never have let that happen, good times!\" "
                    "Again, you hear this name: {0}, you ask the old man, but all he tells you is, that the "
                    "river, which provides the water for the village has become salty for month now. The "
                    "crops cannot grow any longer, the cattle dies, and the villagers are thirsty.",
                    Ressources::urza()));
    Console::br();
    Console::printLn("Do you want to offer some help?");

    if (CMenu::executeAcceptRejectMenu() == CMenu::accept())
    {
        Console::br();
        Console::printLn("You remember what it means, to be a hero, agree to help the poor people.");
        Console::printLn("The root of all their misery seems to be the salty river, so you should go up the stream and "
                         "look for the source of the salt.");
        Console::br();
        CGameManagement::getInstance()->placeTask(new CLakeOfTearsTask());
        return;
    }

    Console::printLn("Salty water is a \"them-problem\" not a \"you-problem\" so you decide to leave them and continue "
                     "your quest as a true, brave and shiny hero.");
}

unsigned int CLakeOfTearsEncounter::encounterChance(const EEncounterType& tp, const std::string_view& moduleName) const
{
    return 5;
}

std::string CLakeOfTearsEncounter::name() const
{
    return std::format("{0}Sta{1}rving villag{0}ers{1}", CC::fgYellow(), CC::ccReset());
}

std::string CLakeOfTearsEncounter::moduleName() const
{
    return LakeTearsRessources::moduleName();
}
