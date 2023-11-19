#include "fishingvillage/town/cfishingvillage.h"
#include "fishingvillage/town/cfishingfritz.h"
#include "fishingvillage/town/cfishrestaurant.h"
#include "fishingvillage/town/cgofishing.h"

#include "cgamemanagement.h"
#include "cmenu.h"
#include "colorize.h"
#include "console.h"
#include "fishingvillage/moduleressources.h"

#include <format>

CFishingVillage::CFishingVillage()
{
    _description = "";

    _encounterType = CEncounter::EEncounterType::eNone;
    _isTaskPossible = false;
    _showInFogOfWar = true;
}

void CFishingVillage::execute()
{
    CField::execute();

    printHeader();

    Console::printLn(std::format(
        "A smaly, idyllic fishing village, placed next to {0}, the lake which gave this little village its name. There "
        "is a tavern, famous for its fish meals, and {1} a legendary fisherman. Roumors say, that once in a while, you "
        "can eat {2} here, a delicacy that is so rare, because the {2} is extremely hard to catch.",
        FishingVillageRessources::fishingVilleName(),
        FishingVillageRessources::fishingFritz(),
        FishingVillageRessources::getFish(FishingVillageRessources::EFishLevel::eLegend)));
    Console::br();

    CMenu menu;
    menu.addMenuGroup(
        {menu.createAction(FishingVillageRessources::fishingFritz(), 'f'), menu.createAction("Restaurant", 'R')});
    menu.addMenuGroup({menu.createAction("Go Fishing", 'G')}, {CMenu::exit()});

    CMenu::Action input;
    do
    {
        input = menu.execute();
        if (input.key == 'f')
        {
            CFishingFritz f;
            f.execute();
        }
        if (input.key == 'r')
        {
            CFishRestaurant f;
            f.execute();
        }
        if (input.key == 'g')
        {
            CGoFishing f;
            f.execute();
        }
        printHeader();

    } while (input != CMenu::exit());
}

std::string CFishingVillage::mapSymbol() const
{
    return "~";
}

std::string CFishingVillage::bgColor() const
{
    return CC::bgLightBlue();
}

std::string CFishingVillage::fgColor() const
{
    return CC::fgWhite();
}

void CFishingVillage::printHeader()
{
    Console::cls();

    Console::printLn(FishingVillageRessources::fishingVilleName(), Console::EAlignment::eCenter);
    Console::printLn("Local recreation area", Console::EAlignment::eCenter);
    Console::br();

    Console::printLn(std::format(
        "A smaly, idyllic fishing village, placed next to {0}, the lake which gave this little village its name. There "
        "is a tavern, famous for its fish meals, and {1} a legendary fisherman. Roumors say, that once in a while, you "
        "can eat {2} here, a delicacy that is so rare, because the {2} is extremely hard to catch.",
        FishingVillageRessources::fishingVilleName(),
        FishingVillageRessources::fishingFritz(),
        FishingVillageRessources::getFish(FishingVillageRessources::EFishLevel::eLegend)));
    Console::br();
}
