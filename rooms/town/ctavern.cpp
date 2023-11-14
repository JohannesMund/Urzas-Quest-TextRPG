#include "ctavern.h"
#include "cbountyhunt.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "console.h"
#include "randomizer.h"
#include "ressources.h"

#include <format>

CTavern::CTavern()
{
}

void CTavern::execute()
{
    CMenu::Action input;
    CMenu menu;
    std::vector<CMenu::Action> navs;
    navs.push_back(menu.createAction("Rumors"));

    if (!CBountyHunt::isHuntActive())
    {
        navs.push_back(menu.createAction("Bounty Hunt"));
    }
    menu.addMenuGroup(navs, {CMenu::exit()});

    do
    {
        Console::cls();
        Console::printLn("Aaah, the tavern. Time for a rest, time for a cool ale! The tavern is crowded with hard "
                         "drunkards and easy girls. The place to be in any fantasy setting.");
        Console::hr();

        input = menu.execute();

        if (input.key == 'r')
        {
            Console::printLn("You walk around in the tavern, talk to the people and listen to some conversations, "
                             "Obviously, the one thing, everybody seems to be talking about is:");
            Console::br();
            Console::printLn(Ressources::Rooms::getRandomRumor(), Console::EAlignment::eCenter);
            Console::br();
            Console::confirmToContinue();
        }

        if (input.key == 'b')
        {
            bountyHunt();
            Console::confirmToContinue();
        }

    } while (input != CMenu::exit());
}

void CTavern::bountyHunt()
{
    Console::printLn("You approach the big board on the wall with the headline \"Wanted\". The worst criminals of the "
                     "countra are displayed here, and big rewards are for those who can catch one of those villains.");
    Console::printLn("The most interesting one is:");
    Console::br();
    auto bounty = Ressources::Enemies::getRandomBountyName();
    Console::printLn(bounty.first, Console::EAlignment::eCenter);
    Console::printLn("wanted for:", Console::EAlignment::eCenter);
    Console::printLn(bounty.second, Console::EAlignment::eCenter);
    Console::br();

    auto reward = CGameManagement::getPlayerInstance()->level() * 1500 +
                  Randomizer::getRandom(CGameManagement::getPlayerInstance()->level() * 250);

    Console::printLn(std::format("Reward: {} Gold", reward));
    Console::printLn("This guy shure looks dangerous, but the reward should be worth it. But the guy looks dangerous.");
    Console::hr();

    if (CMenu::executeAcceptRejectMenu() == CMenu::accept())
    {
        Console::printLn("You feel brave and relentless, and decide to hunt this sucker down. You rip of his poster, "
                         "ask around for his whereabouts and start your hunt");
        auto bountyHunt = new CBountyHunt(bounty.first, reward);
        CGameManagement::getInstance()->placeTask(bountyHunt);
    }
}
