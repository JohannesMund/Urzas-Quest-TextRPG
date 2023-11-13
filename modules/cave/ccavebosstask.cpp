#include "ccavebosstask.h"
#include "cbattle.h"
#include "ccaveboss.h"
#include "cgamemanagement.h"
#include "console.h"
#include "moduleressources.h"

CCaveBossTask::CCaveBossTask(bool* bossDefeated) : CTask(), _bossDefeated(bossDefeated)
{
}

void CCaveBossTask::execute()
{
    CCaveBoss boss;
    boss.printBossBattleHeader();
    Console::printLn("There he is, you encounter the boss of this cave");
    Console::br();
    Console::confirmToContinue();

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
        CGameManagement::getProgressionInstance()->reportModuleFinished(CaveRessources::moduleName());
    }
}
