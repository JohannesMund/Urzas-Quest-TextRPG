#include "csewerencounter.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "colorize.h"
#include "console.h"
#include "csewertask.h"
#include "ctown.h"
#include "moduleressources.h"

#include <format>
#include <string>

CSewerEncounter::CSewerEncounter()
{
    _isSingleExecution = true;
    _type = CEncounter::eTown;
}

void CSewerEncounter::execute(const std::string_view& moduleName)
{
    CEncounter::execute(moduleName);

    std::string townName;
    auto town = dynamic_cast<CTown*>(CGameManagement::getInstance()->currentRoom());
    if (town != nullptr)
    {
        townName = town->name();
    }

    Console::printLn(
        std::format("As you enter {}, the whole town is in an uproar. People running around, chattering, some are "
                    "crying, one woman is even screaming. Something is utterly wrong here. As soon as some of the "
                    "people recognize you as the big hero you are, the come up to you and ask, whether you could help.",
                    townName));
    Console::printLn(std::format(
        "Obviously something is going on in the {}sewers{} of {}, and this time, some children disappeared.",
        CC::fgYellow(),
        CC::ccReset(),
        townName));
    Console::printLn("Do you accept your new quest?");
    Console::br();

    if (CMenu::executeAcceptRejectMenu() == CMenu::reject())
    {
        Console::printLn("You decide not to. You give the townsfolk a lecture about \"You-Problems vs. Me-Problems\", "
                         "and reject their quest.");
        Console::printLn(
            "At least, they understand. The shop is still open for you and the tavern sells you some "
            "beer. The Barkeeper probably spit into it, and you should definitely check the equipment you buy today.");
        return;
    }

    Console::printLn(
        "Of course you will! This is what you are here for. The townspeople show you the entry to the sewer and you "
        "decide to take some rest, stack up on equipment, and start searching for the kids as soon as possible.");

    town->setTask(new CSewerTask());
    _hasBeenExecuted = true;
}

unsigned int CSewerEncounter::encounterChance(const EEncounterType&, const std::string_view&) const
{
    return 5;
}

std::string CSewerEncounter::name() const
{
    return SewerRessources::encounterName();
}

std::string CSewerEncounter::moduleName() const
{
    return SewerRessources::moduleName();
}

bool CSewerEncounter::canBeExecuted(const EEncounterType& tp) const
{
    if (CGameManagement::getInstance()->currentRoom()->isTaskPossible())
    {
        return CEncounter::canBeExecuted(tp);
    }
    return false;
}
