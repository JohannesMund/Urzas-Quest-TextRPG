#include "cfindguardstask.h"
#include "../enemies/ccannibalhorde.h"
#include "cbattle.h"
#include "ccapital.h"
#include "cgamemanagement.h"
#include "cleilarescuecapitaltask.h"
#include "cmenu.h"
#include "colorize.h"
#include "console.h"

#include <cmath>
#include <format>

CFindGuardsTask::CFindGuardsTask(const unsigned int number) : _number(number)
{
}

void CFindGuardsTask::execute()
{
    switch (_number)
    {
    case 0:
    default:
        findFirstGuard();
        break;
    case 1:
        rescueGuardFromMafia();
        break;
    case 2:
        fightCannibalHorde();
        break;
    }
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
    Console::printLn(
        "You find the first of the gurads, you know the guy, you treated his wounds after his first beat-up by the "
        "rebellion. He recognizes you and after some short explainations, he agrees to help.");
    Console::printLn(std::format("But unfortunately, he and the other guards scattered and lost each other. Most "
                                 "probaby the others are in danger, not only are they bad at their jobs as guards, but "
                                 "they are also not used to to wild live outside the capital. You will have to find "
                                 "all {}, and together, they will come up with a plan how to get into the dungeon.",
                                 _maxNumber));
    finishTask();
}

void CFindGuardsTask::rescueGuardFromMafia()
{
    if (_mafiaMoney == _mafiaStartingMoney)
    {
        Console::printLn(
            "This one really put himself into he hell of a mess. he is surrounded by several heavy armed "
            "mafia dudes, lead by the boss dude, nobody is looking happy, espesially not the guard. It seems to be "
            "about money. it s always about monay. Looking at the number of mafia dudes and their weapons,  attacking "
            "is not an option, especially, if you want to get the guard out there alive, or at least in one piece.");
    }
    else
    {
        Console::printLn(
            "Not much has changed in the scene, since last time. Only the mafia bookkeper dude is fiddeling around "
            "with his abacus, and you are sure, the the price to free the guard they asked last time is no longer "
            "valid.");
    }

    if (_mafiaMoney < _maxMafiaMoney)
    {
        _mafiaMoney += std::ceil((_mafiaMoney * _mafiaIntrest) / 100);
    }

    Console::br();
    Console::printLn(
        "The Mafia Boss surveys you with is sharp looks: \"So, you are here to get this guy out? This "
        "will be a problem. This guy owes us money. Much money. But i think i can make you an offer, you cannot "
        "refuse.\" He glances at the bookkeper dude. \"Tell our businney partner, how much does his life cost?\"");
    Console::printLn(
        std::format("The bookkeeper dude looks at his abacus and tells you the amount: \"Including "
                    "intrest, special intrest, delay intrest, and special delay inrest, it is {}{} Gold{}.\"",
                    CC::fgYellow(),
                    _mafiaMoney,
                    CC::ccReset()));

    CMenu menu;

    auto pay = menu.createAction(std::format("Pay the dude ({} Gold)", _mafiaMoney), 'G');
    if (CGameManagement::getPlayerInstance()->gold() >= (int)_mafiaMoney)
    {
        Console::printLn("A lot of money for such a mess of a guy. But... you need his help.");
        menu.addMenuGroup({pay}, {CMenu::exit()});
    }
    else
    {
        Console::printLn(
            "This is a lot of money! Too much, you just dont have enough. Looking into the eyes of the guard, you see "
            "his desperation grow, and his hope shrink. You almost feel sorry for that guy.");
        menu.addMenuGroup({}, {CMenu::exit()});
    }
    if (menu.execute() == pay)
    {
        Console::printLn(std::format(
            "Ok, time to play it cool. You grab your money bag an throw {}{} Gold{} on the table. the bookkeeper dude "
            "looks suspiciously and counts the money. Twice. This takes like ages, but in the end he nods to his boss.",
            CC::fgYellow(),
            _mafiaMoney,
            CC::ccReset()));
        Console::printLn("The messed up guard looks relieved as the mafia dudes set him free. you grab him and leave.");
        CGameManagement::getPlayerInstance()->spendGold(_mafiaMoney);
        finishTask();
        return;
    }

    Console::printLn(std::format(
        "Not this time. You will have to come back. Or maybe not. Maybe there is another way to rescue {0}. Oh please, "
        "let there be another way to rescue {0}! The probably is no other way to rescue {0}",
        Ressources::Game::princessLeila()));
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
