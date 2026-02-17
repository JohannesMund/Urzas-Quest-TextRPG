#include "cdancingbard.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "console.h"
#include "ctown.h"
#include "moduleressources.h"
#include "randomizer.h"
#include "ressources.h"

#include <format>

CDancingBard::CDancingBard()
{
    _isSingleExecution = true;
    _type = CEncounter::eTown;
}

void CDancingBard::execute(const std::string_view& moduleName)
{
    CEncounter::execute(moduleName);
    _hasBeenExecuted = true;

    std::string townName;
    auto town = dynamic_cast<CTown*>(CGameManagement::getInstance()->currentRoom());
    if (town != nullptr)
    {
        townName = town->name();
    }

    Console::printLn(
        std::format("Entering {}, you see a huge uproar on the marketplace of the town. You go closer to see, what's "
                    "going on and see, that the {} is in town.",
                    townName,
                    name()));
    Console::printLn("This seems to be a welcomne Destraction from your hard adventurer chores, so you decide to watch "
                     "the show. This guy sure knows entertainment!");
    Console::printLn(std::format("The {} is singing and dancing an playing various instruments. The crowd sings along "
                                 "and dances and cheers and everybody has a great time.",
                                 name()));
    Console::printLn(std::format(
        "At the climax of his show, the {} sings a song, everybody seems to know. Again and again everybody shouts:",
        name()));
    Console::br();
    Console::printLn(Ressources::Game::urzaWhoTheFuckIsUrza(), Console::EAlignment::eCenter);
    Console::br();
    Console::printLn(std::format(
        "This song touches you. So much, that you really start to poner, who on earth this {}Ur{}za{} might be.",
        CC::fgGreen(),
        CC::fgLightGreen(),
        CC::ccReset()));

    Console::printLn(std::format("In the end, you still don't know, who this {}Ur{}za{} - dude{} is, but you still "
                                 "learned something, so it is just fair to earn some Experience.",
                                 CC::fgYellow(),
                                 CC::fgGreen(),
                                 CC::fgYellow(),
                                 CC::ccReset()));

    CGameManagement::getPlayerInstance()->addXp(Randomizer::getRandom(5) + 1);
    CGameManagement::getProgressionInstance()->reportModuleFinished(Bard::moduleName());
}

unsigned int CDancingBard::encounterChance(const EEncounterType&, const std::string_view&) const
{
    return 5;
}

std::string CDancingBard::name() const
{
    return Bard::encounterName();
}

std::string CDancingBard::moduleName() const
{
    return Bard::moduleName();
}

std::string CDancingBard::translatorModuleName() const
{
    return Bard::moduleName();
}
