#include "csewerdungeon.h"
#include "cgamemanagement.h"
#include "console.h"
#include "csewerbattleencounter.h"
#include "csewerbossroom.h"
#include "moduleressources.h"

CSewerDungeon::CSewerDungeon()
{
}

void CSewerDungeon::execute()
{
    CSewerBattleEncounter* encounter = new CSewerBattleEncounter();
    CGameManagement::getInstance()->registerEncounter(encounter);
    dungeonLoop();
    CGameManagement::getInstance()->unregisterEncounterByModuleName(Sewer::dungeonEncounterName());
}

void CSewerDungeon::loopHook()
{
    if (_bossDefeated)
    {
        _map->setExitAvailable();
    }

    if (!_bossAwake)
    {
        if ((_map->seenRooms() > ((_map->roomCount() * 3) / 4)))
        {
            Console::br();
            Console::printLn("After wandering around in this stinking hell hole of a dungeon, you have a pretty good "
                             "idea where to go to. There is this one region, where you always heard the quit whimping "
                             "of children. There you should go.");
            Console::confirmToContinue();
            Console::br();

            _map->addSpecificRoom(new CSewerBossRoom(&_bossDefeated));
            _bossAwake = true;
        }
    }
}
