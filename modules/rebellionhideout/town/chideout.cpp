#include "chideout.h"
#include "../moduleressources.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "colorize.h"
#include "console.h"
#include "randomizer.h"

CHideout::CHideout() : CTownModule(SandwichShop::sandwichShopName())
{
}

void CHideout::execute()
{

    CMenuAction input;
    do
    {
        Console::cls();

        Console::printLn(SandwichShop::rebellionHideoutName(), Console::EAlignment::eCenter);
        Console::br();
        Console::printLn(
            tr("You enter the employees bathroom (which is, as you know now, not totally necessary, since you "
               "still "
               "don't "
               "have any employees but you have a rebellion base in your shop, and with big rebellion bases comes "
               "big "
               "responsibility.), move away the toilet and enter the stairway to the hidden office of {} and {}.",
               Ressources::Game::fiego(),
               Ressources::Game::brock()),
            Console::EAlignment::eCenter);

        CMenu menu(SandwichShop::moduleName());

        CMenuAction talkAction = menu.createAction({"Talk to Rebellion", 'T'});

        menu.addMenuGroup({talkAction}, {CMenu::exit()});

        input = menu.execute();

        if (input == talkAction)
        {
            talkToRebellion();
        }

    } while (input != CMenu::exit());
}

CMenuAction CHideout::townModuleNav(CMenu& menu) const
{
    return menu.createAction({CC::unColorizeString(SandwichShop::rebellionHideoutName()), 'H'}, false);
}

std::string CHideout::translatorModuleName() const
{
    return SandwichShop::moduleName();
}

std::string CHideout::translatorObjectName() const
{
    return std::string(TagNames::RebellionHideout::rebellionHideout);
}

void CHideout::talkToRebellion()
{
    Console::printLn(
        tr("You enter the employees bathroom (which is, as you know now, not totally necessary, since you still don't "
           "have any employees but you have a rebellion base in your shop, and with big rebellion bases comes big "
           "responsibility.), move away the toilet and enter the stairway to the hidden office of {} and {}.",
           Ressources::Game::fiego(),
           Ressources::Game::brock()));

    if (CGameManagement::getProgressionInstance()->areModuleQuestsAvailable())
    {
        auto quest = CGameManagement::getProgressionInstance()->getRandomQuest();

        Console::printLn(
            tr("As you arrive, {} and {} start rummaging in their papers and eventually pull out a crumpled sheet. "
               "There is a job to be done for the glory of the rebellion. You take a look at the "
               "paper and read the instruction:",
               Ressources::Game::fiego(),
               Ressources::Game::brock()));
        Console::br();
        Console::printLn(quest.questText, Console::EAlignment::eCenter);
        Console::br();
        Console::printLn(tr("Do you accept this task?"));
        Console::br();
        if (CMenu::executeAcceptRejectMenu() == CMenu::accept())
        {
            Console::br();
            Console::printLn(
                tr("For the well-being of the land! For the rebellion! For {}! You accept the task, and leave.",
                   Ressources::Game::princessLeila()));
            CGameManagement::getProgressionInstance()->acceptModuleQuest(quest.moduleName);
        }
        else
        {
            Console::br();
            Console::printLn(tr("Not today, the whole rebellion thing is still somehow suspisous to you. what are they "
                                "doing in the basement of you shop anyway?"));
        }
    }
    else
    {
        Console::printLn(tr(
            "As you arrive, {} and {} are brainstorming the next actions, the rebellion will take. They are a little "
            "bit uncreative right now, all they come up with is kidnapping {} over and over again. As much as you "
            "would appreciate her beeing around, as much you don't want to kidnap her without any good reason to "
            "do so, so they make clear, that you dont approve any kidnapping operations for now. With this option out "
            "of the way, There seems nothing to be done for now.",
            Ressources::Game::fiego(),
            Ressources::Game::brock(),
            Ressources::Game::leila()));
    }

    Console::confirmToContinue();
}
