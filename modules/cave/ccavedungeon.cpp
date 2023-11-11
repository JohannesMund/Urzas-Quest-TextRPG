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

    if (_bossAwake)
    {
        if (!_bossDefeated)
        {
            _moveCycle++;
            if (_moveCycle > 2)
            {
                _moveCycle = 0;
            }
            if (_moveCycle == 0)
            {
                _map->moveTasks();
            }
        }
    }
    else
    {
        if ((_map->seenRooms() > ((_map->roomCount() * 3) / 4)))
        {
            Console::br();
            Console::printLn("A sudden roar tells you, that the Boss of the Cave appeared.");
            Console::confirmToContinue();
            Console::br();

            _map->addTask(new CCaveBossTask(&_bossDefeated), true);
            _bossAwake = true;
        }
    }
}
