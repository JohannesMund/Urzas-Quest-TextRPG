#include "ccapitaldungeonbosstask.h"
#include "cbattle.h"
#include "cgamemanagement.h"
#include "console.h"
#include "modules/leilarescue/enemies/cguardhorde.h"
#include "modules/leilarescue/moduleressources.h"

CCapitalDungeonBossTask::CCapitalDungeonBossTask(bool* bossDefeated) :
    CTask(TagNames::LeilaRescue::dungeonBoss),
    _bossDefeated(bossDefeated)
{
}

void CCapitalDungeonBossTask::execute()
{
    CGuardHorde boss;
    boss.printBossBattleHeader();
    Console::printLn("The guards attack");
    Console::br();
    Console::confirmToContinue();

    CBattle battle(&boss);
    battle.fight();

    if (boss.isDead())
    {
        Console::confirmToContinue();
        Console::br();
        Console::printLn("Finished!");
        Console::br();

        *_bossDefeated = true;
        _isFinished = true;
        CGameManagement::getPlayerInstance()->removeSupportCompanionsByModuleName(LeilaRescue::moduleName());
        CGameManagement::getProgressionInstance()->reportModuleFinished(LeilaRescue::moduleName());
    }
}
