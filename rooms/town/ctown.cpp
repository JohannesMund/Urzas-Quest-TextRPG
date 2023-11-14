#include "ctown.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "colorconsole.h"
#include "console.h"
#include "ctask.h"
#include "ressources.h"

#include <format>

CTown::CTown() : CRoom()
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
    _isTaskPossible = true;
}

void CTown::execute()
{
    Console::printLn(_name, Console::EAlignment::eCenter);
    Console::br();
    CRoom::execute();

    CMenu::Action input;
    do
    {
        Console::hr();

        CMenu menu;
        std::vector<CMenu::Action> navs = {menu.createAction("Blacksmith"),
                                           menu.createAction("Church"),
                                           menu.createAction("Tavern"),
                                           menu.createAction("Shop")};
        if (CGameManagement::getCompanionInstance()->hasCompanion())
        {
            navs.push_back(menu.createAction("Farm"));
        }

        CMenu::Action taskAction;
        if (hasTask() && !_task->isAutoExecute())
        {
            taskAction = menu.createAction(_task->taskNav());
            navs.push_back(taskAction);
        }
        menu.addMenuGroup(navs, {CMenu::exit()});

        input = menu.execute();

        if (input.key == 'b')
        {
            _blackSmith.execute();
        }
        if (input.key == 'c')
        {
            _church.execute();
        }
        if (input.key == 's')
        {
            _shop.execute();
        }
        if (input.key == 't')
        {
            _tavern.execute();
        }
        if (input.key == 'f')
        {
            _farm.execute();
        }

        if (input == taskAction)
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

std::string CTown::mapSymbol() const
{
    if (hasTask())
    {
        return "!";
    }
    return "T";
}

std::string CTown::name() const
{
    return _name;
}
