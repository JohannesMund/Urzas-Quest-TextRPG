#include "clakeoftearsbosstask.h"
#include "cbattle.h"
#include "cgamemanagement.h"
#include "clakeoftearsboss.h"
#include "cmenu.h"
#include "colorize.h"
#include "console.h"
#include "moduleressources.h"
#include "ressources.h"

#include <format>
#include <string>

CLakeOfTearsBossTask::CLakeOfTearsBossTask() : CTask()
{
}

void CLakeOfTearsBossTask::execute()
{
    Console::printLn("After following the river for too long, after drinking salty water one too many times...");
    Console::printLn(
        "After all that, you seem to found the target of your search. You reach a little lake which seems to be the "
        "spring of the salty river. Huge lily pads are swimming in this river and on the biggest two of the lily pads, "
        "you can see two mermaids. Or better one mermaid on one, what seems to be some kind of merboy or merboyman. "
        "Both are crying crocodile tears. This must be the root cause of the salty river.");
    Console::br();
    Console::printLn("Go closer and have a look?");

    if (CMenu::executeYesNoMenu() == CMenu::no())
    {
        Console::printLn("This is too weird, even for your standards.");
        return;
    }

    Console::printLn(
        std::format("\"Who are you guys?\" you ask. \"{}\", replys the mermaid. \"{}\", the merboyman-thing.",
                    LakeTearsRessources::bimmelchen(),
                    LakeTearsRessources::pimmelchen()));
    Console::printLn(
        std::format("\"And what are you doing here?\", you ask, and realize, that those two are starting to get on "
                    "your nerves. The answer is coming from both simultaneously ans is not much of a surprise "
                    "\"CRYING!!!\". \"And why are you crying?\" Again, both answer simultaneously: \"Because "
                    "everybody is evil and nobody likes us and we want {0} back, and because it is the only thing we "
                    "can do\". You start to understand. You understand everything. You have the whole picture. Ok, all "
                    "but the {0} thing.",
                    Ressources::Game::urza()));

    Console::confirmToContinue();
    CLakeOfTearsBoss boss;
    boss.printBossBattleHeader();
    Console::printLn("\"Do you want a reason to cry?\" You do not wait for an answer, and attack.");
    Console::br();
    Console::confirmToContinue();

    CBattle battle(&boss);
    battle.fight();

    if (CGameManagement::getPlayerInstance()->isDead())
    {
        return;
    }

    _isFinished = true;
    CGameManagement::getProgressionInstance()->reportModuleFinished(LakeTearsRessources::moduleName());
}
