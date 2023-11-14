#include "claylatask.h"
#include "cbattle.h"
#include "cmenu.h"
#include "colorconsole.h"
#include "console.h"
#include "moduleressources.h"

#include "lakeoftears/clakeoftearsboss.h"

#include <format>

CLaylaTask::CLaylaTask()
{
}

void CLaylaTask::execute()
{
    Console::printLn("Following the tracks of highwaymen, who kidnapped a princess is one of the core competences of a "
                     "adventurer/hero, so you found the guys pretty fast.");
    Console::printLn(std::format("The two kidnappers are having a rest, while {} is lying tied up on the cart.",
                                 LaylaRessources::layla()));
    Console::printLn("She IS hot!");
    Console::br();
    Console::printLn("This is gonna be rough!");

    CMenu menu;
    menu.addMenuGroup({menu.createAction("Attack"), menu.createAction("Not yet")});
    if (menu.execute().key == 'n')
    {
        Console::printLn(
            std::format("Not yet, you need preparation, but you will definitively come back {} is really hot!",
                        LaylaRessources::layla()));
        return;
    }

    Console::confirmToContinue();
    CLakeOfTearsBoss boss;
    boss.printBossBattleHeader();
    Console::printLn("\"Do you want a reason to cry?\" You do not wait for an answer, and attack:");
    Console::br();
    Console::confirmToContinue();

    CBattle battle(&boss);
    battle.fight();
}
