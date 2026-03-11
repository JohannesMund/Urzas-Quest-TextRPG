#include "ccavedungeon.h"
#include "ccavebattleencounter.h"
#include "ccavebosstask.h"
#include "ccavedungeonmap.h"
#include "cgamemanagement.h"
#include "console.h"

CCaveDungeon::CCaveDungeon() : CDungeon()
{
}

void CCaveDungeon::execute()
{
    CCaveBattleEncounter* encounter = new CCaveBattleEncounter();
    CGameManagement::getInstance()->registerEncounter(encounter);
    dungeonLoop();
    CGameManagement::getInstance()->unregisterEncounterByModuleName(encounter->moduleName());
}

void CCaveDungeon::loopHook()
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
            Console::printLn("Now, that you have a good overview over the dungeon, you realize, that you are not alone "
                             "with the mobs here. Whenever you move, someone else is moving as well. And this someone "
                             "else is big, and with big i mean BIG, like B-I-G!");
            Console::confirmToContinue();
            Console::br();

            _map->addTaskToDungeonRoom(new CCaveBossTask(&_bossDefeated));
            _bossAwake = true;
        }
    }
}
