#include "claylatask.h"
#include "cbattle.h"
#include "cgamemanagement.h"
#include "claylaboss.h"
#include "claylatowntask.h"
#include "cmenu.h"
#include "colorconsole.h"
#include "console.h"
#include "moduleressources.h"
#include "ressources.h"

#include <format>

CLaylaTask::CLaylaTask()
{
}

void CLaylaTask::execute()
{
    Console::printLn("Following the tracks of highwaymen, who kidnapped a princess is one of the core competences of a "
                     "adventurer/hero, so you found the guys pretty fast.");
    Console::printLn(std::format("The two kidnappers are having a rest, while {} is lying tied up on the cart.",
                                 Ressources::Game::princessLayla()));
    Console::printLn("She IS hot!");
    Console::br();
    Console::printLn("This is gonna be rough!");

    CMenu menu;
    menu.addMenuGroup({menu.createAction("Attack"), menu.createAction("Not yet")});
    if (menu.execute().key == 'n')
    {
        Console::printLn(
            std::format("Not yet, you need preparation, but you will definitively come back {} is really hot!",
                        Ressources::Game::princessLayla()));
        return;
    }

    CLaylaBoss boss;
    boss.printBossBattleHeader();
    Console::printLn(
        std::format("\"I am coming for your rescue, princess\" You scream in the direction of {}, and attack:",
                    Ressources::Game::princessLayla()));
    Console::br();
    Console::confirmToContinue();

    CBattle battle(&boss);
    battle.fight();

    Console::printLn(std::format("After putting the two rouges to flight you turn to {0}, untie her und guard her to "
                                 "the next town. Unfortunately {0} is a real princess and does not show the slightest "
                                 "bit of interest for you, the hero. But man, she is hot!",
                                 Ressources::Game::princessLayla()));
    Console::printLn(
        std::format("Nevertheless, you heard two new interesting names, {0} and {1} and decide, that if nobody tells "
                    "you about {2}, you shoul head to the next town and see, what you can learn about {0} and {1}.",
                    Ressources::Game::fiego(),
                    Ressources::Game::brock(),
                    Ressources::Game::urza()));

    CGameManagement::getInstance()->placeTaskOnTown(new CLaylaTownTask);
    _isFinished = true;
}
