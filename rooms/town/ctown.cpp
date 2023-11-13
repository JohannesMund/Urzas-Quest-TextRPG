#include "ctown.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "colorconsole.h"
#include "console.h"
#include "ressources.h"

#include <format>

CTown::CTown()
{
    auto town = Ressources::Rooms::getRandomTown();
    _name = town.first;
    _description = town.second;

    _shop.setCityName(_name);
    _church.setCityName(_name);
    _farm.setCityName(_name);
    _blackSmith.setCityName(_name);
    _tavern.setCityName(_name);

    _encounterPossible = true;
    _taskPossible = true;
}

void CTown::execute()
{
    Console::printLn(_name, Console::EAlignment::eCenter);
    Console::br();

    CRoom::execute();
    if (_encounterPossible && !hasTask())
    {
        CGameManagement::getInstance()->executeRandomEncounter(CEncounter::eTown);
    }

    CMenu menu;
    std::vector<CMenu::Action> navs = {menu.createAction("Blacksmith"),
                                       menu.createAction("Church"),
                                       menu.createAction("Tavern"),
                                       menu.createAction("Shop")};
    if (CGameManagement::getCompanionInstance()->hasCompanion())
    {
        navs.push_back(menu.createAction("Farm"));
    }

    menu.addMenuGroup(navs, {CMenu::exitAction()});

    CMenu::Action input;
    do
    {
        Console::hr();
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
        Console::cls();
        Console::printLn(_name, Console::EAlignment::eCenter);
        Console::br();
        Console::printLn(_description);

    } while (!CMenu::exit(input));
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
