#include "cchurch.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "console.h"

#include <format>
CChurch::CChurch()
{
}

void CChurch::execute()
{
    CMenu menu;
    CMenuAction blessingAction = menu.createAction("Get Blessing", 'b');
    menu.addMenuGroup({blessingAction}, {CMenu::exit()});

    CMenuAction input;
    do
    {
        Console::cls();
        Console::printLn(std::format(
            "The church of {}. An old church, but nice and clean. The priest is an old, friedly man.", _cityName));
        Console::hr();

        input = menu.execute();

        if (input == blessingAction)
        {
            Console::printLn(
                "The priest chants his prayers and a godly light surrounds you. Your wounds close, your pain "
                "vanishes.");
            Console::printLn("You are fully healed.");
            CGameManagement::getPlayerInstance()->fullHeal();
            Console::confirmToContinue();
        }

    } while (input != CMenu::exit());
}
