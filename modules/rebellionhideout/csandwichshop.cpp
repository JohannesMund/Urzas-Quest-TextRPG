#include "csandwichshop.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "colorize.h"
#include "console.h"
#include "csandwich.h"
#include "moduleressources.h"

#include <format>

CSandwichShop::CSandwichShop()
{
    replaceSandwichOfTheDay();

    _description = "";

    _encounterType = CEncounter::EEncounterType::eNone;
    _isTaskPossible = true;
    _showInFogOfWar = true;
}

void CSandwichShop::execute()
{
    CRoom::execute();
    if (CGameManagement::getProgressionInstance()->turns() - _turns > Ressources::Config::turnsUntilShopRefresh)
    {
        replaceSandwichOfTheDay();
    }

    printHeader();

    if (_playerOwnsShop)
    {
        sellSandwiches();
    }
    else
    {
        showSandwichOfTheDay();
    }
}

std::string CSandwichShop::bgColor() const
{
    return CC::bgGreen();
}

std::string CSandwichShop::fgColor() const
{
    return CC::fgLightYellow();
}

CMap::RoomFilter CSandwichShop::sandwichShopFilter()
{

    return [](const CRoom* room) { return dynamic_cast<const CSandwichShop*>(room) != nullptr; };
}

void CSandwichShop::printHeader()
{
    Console::cls();
    Console::printLn(std::format("{}", RebellionHideoutRessources::sandwichShopName()), Console::EAlignment::eCenter);
    Console::printLn("Ye olde Sandwich Shoppe, est. 489 ad. dragonis", Console::EAlignment::eCenter);
    Console::br();
}

void CSandwichShop::showSandwichOfTheDay()
{
    Console::printLn(
        std::format("The Sandwich shop is run by {}, an old man with a dream, who once started this shop "
                    "to make the perfect sandwich, but after years and years of making and selling "
                    "sandwiches lost all of his spirits. His sandwiches are still great though, but he reduced the "
                    "menu to one single sandwich of the day, written on the sign next to the counter",
                    RebellionHideoutRessources::mrSoop()));
    Console::br();
    Console::printLn("Sandwich of the day:", Console::EAlignment::eCenter);
    Console::printLn(_sandwiches.at(0)->description(), Console::EAlignment::eCenter);
    Console::br();

    CMenu menu;

    if (CGameManagement::getPlayerInstance()->gold() >= _sandwiches.at(0)->value())
    {
        menu.addMenuGroup(
            {menu.createAction(std::format("Eat Sandwich of the Day ({} Gold)", _sandwiches.at(0)->value()), 'E')},
            {CMenu::exit()});
    }
    else
    {
        menu.addMenuGroup(
            {menu.createAction(std::format("Eat Sandwich of the Day ({} Gold)", _sandwiches.at(0)->value()), 'E')},
            {CMenu::exit()});
    }

    if (menu.execute().key == 'e')
    {
        eatSandwichOfTheDay();
    }
}

void CSandwichShop::eatSandwichOfTheDay()
{
    _sandwiches.at(0)->useFromInventory();
    replaceSandwichOfTheDay();
}

void CSandwichShop::sellSandwiches()
{
}

char CSandwichShop::getMapSymbol() const
{
    return 'S';
}

void CSandwichShop::replaceSandwichOfTheDay()
{
    _turns = CGameManagement::getProgressionInstance()->turns();
    for (auto i : _sandwiches)
    {
        delete i;
    }
    _sandwiches.clear();

    _sandwiches.push_back(CGameManagement::getItemFactoryInstance()->sandwichMaker());
}
