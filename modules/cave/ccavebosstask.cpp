#include "ccavebosstask.h"
#include "cbattle.h"
#include "ccaveboss.h"
#include "console.h"
#include "moduleressources.h"

CCaveBossTask::CCaveBossTask(bool* bossDefeated) : CTask(), _bossDefeated(bossDefeated)
{
}

void CCaveBossTask::execute()
{
    Console::printLn("There he is, you encounter the boss of this cave");
    Console::br();
    Console::printLn(CaveRessources::getColoredBosString(), Console::EAlignment::eCenter);
    Console::br();
    Console::confirmToContinue();

    CCaveBoss boss;
    CBattle battle(&boss);
    battle.fight();

    if (boss.isDead())
    {
        Console::confirmToContinue();
        Console::br();
        Console::printLn("Finished! time to leave this hellhole.");
        Console::br();

        *_bossDefeated = true;
        _isFinished = true;
    }
}
