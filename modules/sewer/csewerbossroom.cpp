#include "csewerbossroom.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "colorconsole.h"
#include "console.h"
#include "csewerboss.h"
#include "moduleressources.h"

#include <format>

CSewerBossRoom::CSewerBossRoom(bool* isBossDefeated)
{
    _description = SewerRessources::getBossRoomDescription();
    _showInFogOfWar = true;
    _bossDefeated = isBossDefeated;
    _seen = true;
    _isTaskPossible = false;
    _encounterType = CEncounter::EEncounterType::eNone;
}

void CSewerBossRoom::execute()
{
    CDungeonRoom::execute();

    if (*_bossDefeated == true)
    {
        return;
    }

    Console::br();
    Console::printLn(
        "Nevertheless, from a small room you can clearly hear the missing children. And something else...");
    Console::printLn("Do you want to free the children now?");

    if (CMenu::no(CMenu::executeYesNoMenu()))
    {
        Console::printLn("You are not done yet. You will return later.");
        return;
    }

    CSewerBoss boss;
    boss.printBossBattleHeader();
    Console::printLn("You enter the small room and see the children you are looking for. And what took "
                     "them here.");
    Console::br();
    Console::confirmToContinue();

    CBattle battle(&boss);
    battle.fight();

    if (boss.isDead())
    {
        Console::confirmToContinue();
        Console::br();
        Console::printLn("Finished! time to take the children and return to somwhere where you can breathe.");
        Console::br();

        *_bossDefeated = true;
        CGameManagement::getProgressionInstance()->reportModuleFinished(SewerRessources::moduleName());
    }
}

std::string CSewerBossRoom::mapSymbol() const
{
    return "O";
}

bool CSewerBossRoom::isSpecialRoom() const
{
    return true;
}
