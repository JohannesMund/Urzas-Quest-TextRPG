#include "fishingvillage/cfishingvillage.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "colorize.h"
#include "console.h"
#include "ctask.h"
#include "fishingvillage/moduleressources.h"

#include "cfishingvillage.h"
#include <format>
#include <optional>

CFishingVillage::CFishingVillage() : CRoom(TagNames::FishingVille::fishingVille)
{
    _description = "";

    _encounterType = CEncounter::EEncounterType::eNone;
    _isRandomTaskPossible = true;
    _showInFogOfWar = true;
}

void CFishingVillage::execute()
{
    CRoom::execute();
    printHeader();

    CMenuAction input;
    do
    {
        CMenu menu(FishingVillageMakeRod::moduleName());

        CMenuAction fritzAction = menu.createAction({CC::unColorizeString(Ressources::Game::fishingFritz()), 'f'});
        CMenuAction restaurantAction = menu.createAction({"Restaurant", 'R'});
        CMenuAction fishingAction = menu.createAction({"Go Fishing", 'G'});

        menu.addMenuGroup({fritzAction, restaurantAction, fishingAction});

        std::optional<CMenuAction> taskAction = {};
        if (hasTask() && !_task->isAutoExecute())
        {
            taskAction = menu.createAction({_task->taskNav()}, false);
            menu.addMenuGroup({taskAction.value()}, {CMenu::exit()});
        }
        else
        {
            menu.addMenuGroup({}, {CMenu::exit()});
        }

        input = menu.execute();
        if (input == fritzAction)
        {
            _fishingFritz.execute();
        }
        if (input == restaurantAction)
        {
            _fishRestaurant.execute();
        }
        if (input == fishingAction)
        {
            _goFishing.execute();
        }
        if (taskAction.has_value() && input == *taskAction)
        {
            executeTask();
            Console::confirmToContinue();
        }
        printHeader();

    } while (input != CMenu::exit());
}

std::string CFishingVillage::bgColor() const
{
    return CC::bgLightBlue();
}

std::string CFishingVillage::fgColor() const
{
    return CC::fgWhite();
}

CMap::RoomFilter CFishingVillage::fishingVillageFilter()
{
    return [](const CRoom* room) { return dynamic_cast<const CFishingVillage*>(room) != nullptr; };
}

void CFishingVillage::printHeader()
{
    Console::cls();

    Console::printLn(FishingVillage::fishingVilleName(), Console::EAlignment::eCenter);
    Console::printLn("Local recreation area", Console::EAlignment::eCenter);
    Console::br();

    Console::printLn(std::format(
        "A smaly, idyllic fishing village, placed next to {0}, the lake which gave this little village its name. There "
        "is a tavern, famous for its fish meals, and {1} a legendary fisherman. Roumors say, that once in a while, you "
        "can eat {2} here, a delicacy that is so rare, because the {2} is extremely hard to catch.",
        FishingVillage::fishingVilleName(),
        Ressources::Game::fishingFritz(),
        FishingVillage::getFish(FishingVillage::EFishLevel::eLegend)));
    Console::br();
}

char CFishingVillage::getMapSymbol() const
{
    return '~';
}
