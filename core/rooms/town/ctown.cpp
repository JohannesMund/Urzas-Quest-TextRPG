#include "ctown.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "colorize.h"
#include "console.h"
#include "ctask.h"
#include "ressources.h"

#include <format>
#include <optional>

CTown::CTown(const std::string_view& objectName) : CRoom(objectName)
{
    auto town = Ressources::Rooms::getRandomTown();
    _name = town.first;
    _description = town.second;

    _shop.setCityName(_name);
    _church.setCityName(_name);
    _farm.setCityName(_name);
    _blackSmith.setCityName(_name);
    _tavern.setCityName(_name);

    _encounterType = CEncounter::EEncounterType::eTown;
    _isRandomTaskPossible = true;
}

void CTown::execute()
{
    Console::printLn(_name, Console::EAlignment::eCenter);
    Console::br();
    CRoom::execute();

    CMenuAction input;
    do
    {
        Console::hr();

        CMenu menu;
        CMenuAction blacksmithAction = menu.createAction({"Blacksmith"});
        CMenuAction churchAction = menu.createAction({"Church"});
        CMenuAction tavernAction = menu.createAction({"Tavern"});
        CMenuAction shopAction = menu.createAction({"Shop"});
        CMenuAction farmAction = menu.createAction({"Farm"});

        CMenu::ActionList navs = {blacksmithAction, churchAction, tavernAction, shopAction};

        if (CGameManagement::getCompanionInstance()->hasCompanion())
        {
            navs.push_back(farmAction);
        }

        menu.addMenuGroup(navs, {CMenu::exit()});

        std::optional<CMenuAction> taskAction = {};
        if (hasTask() && !_task->isAutoExecute())
        {
            taskAction = menu.createAction({_task->taskNav()}, false);
            menu.addMenuGroup({taskAction.value()});
        }

        input = menu.execute();

        if (input == blacksmithAction)
        {
            _blackSmith.execute();
        }
        if (input == churchAction)
        {
            _church.execute();
        }
        if (input == shopAction)
        {
            _shop.execute();
        }
        if (input == tavernAction)
        {
            _tavern.execute();
        }
        if (input == farmAction)
        {
            _farm.execute();
        }

        if (taskAction.has_value() && input == *taskAction)
        {
            executeTask();
            Console::confirmToContinue();
        }

        Console::cls();
        Console::printLn(_name, Console::EAlignment::eCenter);
        Console::br();
        Console::printLn(_description);

    } while (input != CMenu::exit());
}

std::string CTown::bgColor() const
{
    return CC::bgDarkGray();
}

std::string CTown::fgColor() const
{
    return CC::fgLightGray();
}

std::string CTown::name() const
{
    return _name;
}

CMap::RoomFilter CTown::townFilter()
{
    return [](const CRoom* room) { return dynamic_cast<const CTown*>(room) != nullptr; };
}

std::string CTown::translatorModuleName() const
{
    return std::string();
}

char CTown::getMapSymbol() const
{
    return 'T';
}

nlohmann::json CTown::save() const
{
    nlohmann::json o = CRoom::save();
    o["name"] = _name;
    return o;
}

void CTown::load(const nlohmann::json& json)
{
    _name = json.value<std::string>(TagNames::Room::name, "");
    CRoom::load(json);
}
