#include "cleilatask.h"
#include "cbattle.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "colorize.h"
#include "console.h"
#include "leila/cleilaboss.h"
#include "leila/moduleressources.h"
#include "leila/tasks/cleilatowntask.h"
#include "ressources.h"

#include <format>

CLeilaTask::CLeilaTask() : CTask(TagNames::Leila::leila)
{
}

void CLeilaTask::execute()
{
    Console::printLn(tr("Following the tracks of highwaymen, who kidnapped a princess is one of the core competences of a "
                     "adventurer/hero, so you found the guys pretty fast."));
    Console::printLn(tr("The two kidnappers are having a rest, while {} is lying tied up on the cart.",
                                 Ressources::Game::princessLeila()));
    Console::printLn(tr("She IS hot!"));
    Console::br();
    Console::printLn(tr("This is gonna be rough!"));

    CMenu menu(Leila::moduleName());

    auto attackAction = menu.createAction({"Attack"});
    auto notYetAction = menu.createAction({"Not yet"});

    menu.addMenuGroup({attackAction, notYetAction});
    if (menu.execute() == notYetAction)
    {
        Console::printLn(tr(
            "Not yet, you need preparation, but you will definitively come back {} is really hot!",
            Ressources::Game::princessLeila()));
        return;
    }

    CLeilaBoss boss;
    boss.printBossBattleHeader();
    Console::printLn(tr(
        "\"I am coming for your rescue, princess\" You scream in the direction of {}, and attack.",
        Ressources::Game::princessLeila()));
    Console::br();
    Console::confirmToContinue();

    CBattle battle(&boss);
    battle.fight();

    Console::confirmToContinue();
    Console::printLn(tr("After putting the two rouges to flight you turn to {0}, untie her und guard her to "
                                 "the next town. Unfortunately {0} is a real princess and does not show the slightest "
                                 "bit of interest for you, the hero. But man, she is hot!",
                                 Ressources::Game::princessLeila()));
    Console::printLn(tr(
        "Nevertheless, you heard two new interesting names, {0} and {1} and decide, that if nobody tells "
        "you about {2}, you shoul head to the next town and see, what you can learn about {0} and {1}.",
        Ressources::Game::fiego(),
        Ressources::Game::brock(),
        Ressources::Game::urza()));

    CGameManagement::getInstance()->placeTaskOnTown(new CLeilaTownTask);
    _isFinished = true;
}

std::string CLeilaTask::translatorModuleName() const
{
    return Leila::moduleName();
}
