#include "ccapitaldungeon.h"
#include "cgamemanagement.h"
#include "console.h"
#include "modules/leilarescue/dungeon/ccapitaldungeonbosstask.h"
#include "modules/leilarescue/dungeon/cleilaprisonroom.h"
#include "modules/leilarescue/moduleressources.h"

void CCapitalDungeon::execute()
{
    // CSewerBattleEncounter* encounter = new CSewerBattleEncounter();
    // CGameManagement::getInstance()->registerEncounter(encounter);
    dungeonLoop();
    // CGameManagement::getInstance()->unregisterEncounterByModuleName(SewerRessources::dungeonEncounterName());
}

void CCapitalDungeon::loopHook()
{

    if (!_leilaAvailable)
    {
        makeLeilaAvailable();
    }
    else if (!_bossAwake)
    {
        makeBossAvailable();
    }
    else
    {
        makeExitAvailable();
    }
}

void CCapitalDungeon::makeLeilaAvailable()
{
    if (_leilaAvailable)
    {
        return;
    }

    if ((_map->seenRooms() > ((_map->roomCount() * 2) / 4)))
    {
        _leilaAvailable = true;
        _map->addSpecificRoom(new CLeilaPrisonRoom(&_leilaRescued));
    }
}

void CCapitalDungeon::makeBossAvailable()
{
    if (_bossAwake)
    {
        return;
    }
    if (!_leilaRescued)
    {
        return;
    }

    if ((_map->seenRooms() > ((_map->roomCount() * 3) / 4)))
    {
        _bossAwake = true;
        _map->addTask(new CCapitalDungeonBossTask(&_bossDefeated), true);
    }
}

void CCapitalDungeon::makeExitAvailable()
{
    if (_bossDefeated)
    {
        _map->setExitAvailable();
    }
}
