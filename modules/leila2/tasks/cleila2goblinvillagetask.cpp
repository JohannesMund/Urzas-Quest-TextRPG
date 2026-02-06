#include "cleila2goblinvillagetask.h"
#include "cbattle.h"
#include "ccapital.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "console.h"
#include "leila2/enemies/cgoblinhorde.h"
#include "leila2/enemies/cleilabossorks.h"
#include "leila2/moduleressources.h"
#include "leila2/tasks/cleila2capitaltask.h"
#include "ressources.h"

#include <format>

CLeila2GoblinVillageTask::CLeila2GoblinVillageTask() : CTask(TagNames::Leila2::goblinVillage)
{
}

void CLeila2GoblinVillageTask::execute()
{
    Console::printLn(std::format("Here you are, a tiny {0} village. Complete with little huts, a huge bonfire and, "
                                 "of course, a mob of {0}s.",
                                 Leila2::greenskin()));
    Console::printLn(std::format("{} is tied up to a pole in front of the bonfire. She surely is taking her \"damsel "
                                 "in distress\" - role to the limits ",
                                 Ressources::Game::leila()));
    Console::printLn(std::format("Without further ado, you charge the {}s, to end this.", Leila2::greenskin()));
    Console::confirmToContinue();

    CGoblinHorde horde;

    CBattle battle(&horde);
    battle.fight();

    Console::confirmToContinue();

    CLeilaBossOrks boss;
    boss.printBossBattleHeader();
    Console::printLn(std::format(
        "You look at the slain {}s, and realize, that this not over yet. You still have a boss battle in front of you. "
        "\"I am coming for your rescue, princess\" You scream once again, a little less motivated, and attack.",
        Leila2::greenskin(),
        Ressources::Game::princessLeila()));
    CBattle battle2(&boss);
    battle2.fight();

    Console::confirmToContinue();

    Console::printLn(
        "There it is, your first ever genocide. And finally, the princess is save again. But... for how long?");
    Console::printLn(std::format(
        "This does not matter now. You untie the beautiful, sexy princess, and give her back her {}. But instead of "
        "jumping at you and giving you an appropriate \"thank you\" she just makes a disgusted face \"Eeeew, this "
        "thing is all dirty and,... Here, please, keep it as my royal gift, as a reward for your courage.\"",
        Ressources::Game::leilasRibbon()));

    Console::printLn(
        std::format("...and another disappointment, If she just weren't this hot! But at least, now you have a nice, "
                    "beautiful, dirty and a little ripped royal {}, You decide to keep it as a prove for her love.",
                    Ressources::Game::leilasRibbon()));

    auto rooms = CGameManagement::getInstance()->roomsMatchingFilter(CCapital::capitalFilter());
    if (rooms.size())
    {
        rooms.at(0)->setTask(new CLeila2CapitalTask());
    }
    _isFinished = true;
}
