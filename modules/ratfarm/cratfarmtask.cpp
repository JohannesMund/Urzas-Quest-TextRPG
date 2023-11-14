#include "cratfarmtask.h"
#include "cbattle.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "colorconsole.h"
#include "console.h"
#include "cratfarmrat.h"
#include "cratfarmratboss.h"
#include "moduleressources.h"
#include "randomizer.h"

#include <format>

CRatFarmTask::CRatFarmTask()
{
}

void CRatFarmTask::execute()
{
    Console::printLn(
        std::format("Here you are, the {0} farm, with the {0} house of lady {0}. you are a little hungry, maybe ome "
                    "{0}s would help now, but all of a sudden, you realize, that {0}s are not a thing for lady {0}.",
                    RatFarmRessources::getCarrot()));
    Console::printLn(std::format(
        "But this is not what matters now, the {} farm is rat-infected, and you have the job to solve this.",
        RatFarmRessources::getTurnip()));
    Console::printLn("Ready for the battle?");

    if (CMenu::executeYesNoMenu() == CMenu::yes())
    {
        battle();
    }
    else
    {
        Console::printLn("Seeing the rat swarm, you decide, that you are not. maybe later.");
        return;
    }
}

void CRatFarmTask::battle()
{
    for (int i = 0; i < RatFarmRessources::ratCount; i++)
    {
        CRatFarmRat rat;
        CBattle battle(&rat);
        battle.fight();

        if (!rat.isDead())
        {
            return;
        }

        Console::printLn(std::format("This was rat number {}, but there are more rats to go.", i));
        Console::confirmToContinue();
    }

    Console::cls();
    CRatFarmRatBoss ratBoss;
    ratBoss.printBossBattleHeader();
    Console::printLn("After defeating the swarm of rats, the boss of the rats appear.");
    Console::br();
    Console::confirmToContinue();

    CBattle battle(&ratBoss);
    battle.fight();

    if (!ratBoss.isDead())
    {
        return;
    }

    Console::printLn("Thats it! Your first genocide! What a milestone!");
    Console::printLn(std::format("Lady {0} runs toward you and starts thanking you for rescuing her {0} house in {0} "
                                 "vale, and starts stuffing {1} into your pocket",
                                 RatFarmRessources::getCarrot(),
                                 RatFarmRessources::getTurnip()));
    Console::printLn(std::format("You are pondering what is worse, the rats, or the {0}s. You decide, not to think "
                                 "about this any more, and get away, as long you are able to carry all those {0}s",
                                 RatFarmRessources::getTurnip()));
    Console::printLn(std::format("\"May {} bless you!\", is the last thing you hear from lady {}.",
                                 Ressources::Game::urza(),
                                 RatFarmRessources::getCarrot()));
    Console::printLn(std::format("Again, this {} dude. {}??? well you will have to find out.",
                                 Ressources::Game::urza(),
                                 Ressources::Game::whoTheFuckIsUrza()));

    RatFarmRessources::TurnipFactory::addTurnips(Randomizer::getRandom(5) + 7);
    CGameManagement::getProgressionInstance()->reportModuleFinished(RatFarmRessources::moduleName());
    _isFinished = true;
}
