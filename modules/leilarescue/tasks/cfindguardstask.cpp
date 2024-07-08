#include "cfindguardstask.h"
#include "../enemies/ccannibalhorde.h"
#include "cbattle.h"
#include "ccapital.h"
#include "cgamemanagement.h"
#include "cleilarescuecapitaltask.h"
#include "cmenu.h"
#include "colorize.h"
#include "console.h"

#include <format>

CFindGuardsTask::CFindGuardsTask(const unsigned int number)
{
    _number = number;
}

void CFindGuardsTask::execute()
{
}

void CFindGuardsTask::finishTask()
{
    _isFinished = true;
    if (_number < _maxNumber)
    {
        CGameManagement::getInstance()->placeTaskOnField(new CFindGuardsTask(_number + 1));
    }
    else
    {
        CGameManagement::getInstance()->placeTask(new CLeilaRescueCapitalTask(), CCapital::townFilter());
    }
}

void CFindGuardsTask::findFirstGuard()
{
    Console::printLn("");
}

void CFindGuardsTask::rescueGuardFromMafia()
{
}

void CFindGuardsTask::fightCannibalHorde()
{
    Console::printLn(
        "You find this guard, tied to a stick that hangs over a big fire. A lot of savaga people, with little bones "
        "tied in their hairs are standing around the fire holding simple wooden plates and forks. You seem to have "
        "discovered a rare, savage trive of cannibals.");
    Console::printLn("It is already smelling like bacon, so you should hurry, if you want to rescue this guard alive.");

    CMenu menu;
    menu.addMenuGroup({menu.createAction("Attack"), menu.createAction("Retreat")});

    if (menu.execute().key == 'r')
    {
        Console::printLn("There are many cannibals. And you are alone. The guard is a big guy, it will take a while "
                         "until he is well done. you should have the time for more preparations.");
        Console::confirmToContinue();
        return;
    }

    CCannibalHorde horde;
    CBattle battle(&horde);
    battle.fight();

    Console::printLn(
        "Your second genocide. Again, while rescuing the same woman. Well, genocides are daily business for "
        "adventuerers / heros like you. And all genocides where for the greater good.");
    Console::printLn("Of course, if genocides are not the foundation for a good and healthy relationship "
                     "between hero and princess, what else could be?");
    Console::printLn("You untie the guard and lead him to the others.");
    finishTask();
}
