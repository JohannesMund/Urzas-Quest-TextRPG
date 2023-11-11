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
    CMenu::Action input;
    do
    {
        CMenu menu;

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

            CMenu::Action trainingAction = menu.createAction(std::format("Train ({} Gold)", getTrainingCost()));

            if (getTrainingCost() <= CGameManagement::getPlayerInstance()->gold())
            {
                Console::printLn("This sounds like a bargain!");
            }
            else
            {
                Console::printLn("This is too much! a little running around with you should do the same.");
                trainingAction.key = 0;
            }

            menu.addMenuGroup({trainingAction}, {CMenu::exitAction()});
        }
        else
        {
            menu.addMenuGroup({}, {CMenu::exitAction()});
        }

        input = menu.execute();

        if (input.key == 't')
        {
            train();
            Console::confirmToContinue();
        }

    } while (!CMenu::exit(input));
}

void CFarm::train()
{
    Console::printLn(std::format("The farmer disappears with {} for a while and comes back. your {} looks different!",
                                 CGameManagement::getCompanionInstance()->name(),
                                 CGameManagement::getCompanionInstance()->name()));

    CGameManagement::getPlayerInstance()->addGold(getTrainingCost() * -1);
    CGameManagement::getCompanionInstance()->evolve();
}

int CFarm::getTrainingCost() const
{
    return 500 + (CGameManagement::getCompanionInstance()->level() * 500 *
                  CGameManagement::getCompanionInstance()->level() * 3);
}
