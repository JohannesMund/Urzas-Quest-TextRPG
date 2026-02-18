#include "cchurch.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "console.h"

CChurch::CChurch() : CTownModule(TagNames::TownModule::church)
{
}

void CChurch::execute()
{
    CMenu menu;
    CMenuAction blessingAction = menu.createAction({"Get Blessing", 'b'});
    menu.addMenuGroup({blessingAction}, {CMenu::exit()});

    CMenuAction input;
    do
    {
        Console::cls();
        Console::printLn(coreTr(
            "The church of {}. An old church, but nice and clean. The priest is an old, friendly man.", _cityName));
        Console::hr();

        input = menu.execute();

        if (input == blessingAction)
        {
            Console::printLn(
                coreTr("The priest chants his prayers and a godly light surrounds you. Your wounds close, your pain "
                       "vanishes."));
            Console::printLn(coreTr("You are fully healed."));
            CGameManagement::getPlayerInstance()->fullHeal();
            Console::confirmToContinue();
        }

    } while (input != CMenu::exit());
}
