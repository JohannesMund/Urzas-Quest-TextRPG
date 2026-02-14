#include "cratfarmencounter.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "colorize.h"
#include "console.h"
#include "cratfarmtask.h"
#include "moduleressources.h"

#include <format>

CRatFarmEncounter::CRatFarmEncounter()
{
    _isSingleExecution = true;
    _type = CEncounter::eField;
}

void CRatFarmEncounter::execute(const std::string_view& moduleName)
{
    CEncounter::execute(moduleName);

    Console::printLn("And there she is, the crying lady. What crying lady? Well, the crying lady, every hero meets at "
                     "least once during his adventure.");
    Console::printLn(std::format("\"My name is lady {0}, I live in the {0} house on the {0} farm. The "
                                 "{0} farm is located in {0} vale. I am famous for farming the best...\"",
                                 RatFarm::getCarrot()));
    Console::printLn(std::format("\"{}s?\", you interrupt her impolitely", RatFarm::getCarrot()));
    Console::printLn(std::format("\"No, {}s\", she corrects you.", RatFarm::getTurnip()));
    Console::printLn("\"But rats eat all my harvest, please, dear hero, please help me!\"");
    Console::br();
    if (CMenu::executeAcceptRejectMenu() == CMenu::reject())
    {
        Console::printLn(std::format("You dont like {}, you don't like rats, and this lady is strange "
                                     "anyways. You decide to decline and go.",
                                     RatFarm::getTurnip()));
        return;
    }

    Console::printLn(std::format("This lady might be strang, but it is your job, no, your prefession, no your holy "
                                 "duty to save this lady and her {}.",
                                 RatFarm::getTurnip()));

    CGameManagement::getInstance()->placeTaskOnField(new CRatFarmTask());
    _hasBeenExecuted = true;
}

unsigned int CRatFarmEncounter::encounterChance(const EEncounterType&, const std::string_view&) const
{
    return 5;
}

std::string CRatFarmEncounter::name() const
{
    return std::format("Lady {}", RatFarm::getCarrot());
}

std::string CRatFarmEncounter::moduleName() const
{
    return RatFarm::moduleName();
}

std::string CRatFarmEncounter::translatorModuleName() const
{
    return RatFarm::moduleName();
}
