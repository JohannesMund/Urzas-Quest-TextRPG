#include "cfarm.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "console.h"

#include <format>

CFarm::CFarm()
{
}

void CFarm::execute()
{
    CMenuAction input;
    do
    {
        CMenu menu;
        CMenuAction trainAction;

        Console::cls();
        Console::printLn(std::format("Every good town needs a farm. {} has a beautiful one! {} immediately rushes away "
                                     "to play with the many pets around here.",
                                     _cityName,
                                     CGameManagement::getCompanionInstance()->name()));

        if (CGameManagement::getCompanionInstance()->level() < Ressources::Companion::companionLevelCap)
        {
            Console::printLn(
                std::format("The farmer takes a look at your friend. \"he looks great! for sure, he is one "
                            "awesomne {}! But i am sure, with a little training, he could be even better.\"",
                            CGameManagement::getCompanionInstance()->type()));
            Console::printLn("You are intrigued, so you ask for prices.");
            Console::printLn(
                std::format("The farmer takes another, closer look at {}, and replies \"I think, {} is a good price.\"",
                            CGameManagement::getCompanionInstance()->name(),
                            getTrainingCost()));

            if (getTrainingCost() <= CGameManagement::getPlayerInstance()->gold())
            {
                Console::printLn("This sounds like a bargain!");

                trainAction = menu.createShopAction({"Train"}, getTrainingCost());
                menu.addMenuGroup({trainAction}, {CMenu::exit()});
            }
            else
            {
                Console::printLn("This is too much! a little running around with you should do the same.");
                menu.addMenuGroup({}, {CMenu::exit()});
            }
        }
        else
        {
            menu.addMenuGroup({}, {CMenu::exit()});
        }

        input = menu.execute();

        if (input == trainAction)
        {
            train();
            Console::confirmToContinue();
        }

    } while (input != CMenu::exit());
}

void CFarm::train()
{
    Console::printLn(std::format("The farmer disappears with {} for a while and comes back. your {} looks different!",
                                 CGameManagement::getCompanionInstance()->name(),
                                 CGameManagement::getCompanionInstance()->name()));

    CGameManagement::getPlayerInstance()->spendGold(getTrainingCost());
    CGameManagement::getCompanionInstance()->evolve();
}

int CFarm::getTrainingCost() const
{
    return 500 + (CGameManagement::getCompanionInstance()->level() * 500 *
                  CGameManagement::getCompanionInstance()->level() * 3);
}
