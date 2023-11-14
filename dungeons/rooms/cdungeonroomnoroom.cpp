#include "cdungeonroomnoroom.h"

CDungeonRoomNoRoom::CDungeonRoomNoRoom()
{
    _isTaskPossible = false;
    _encounterType = CEncounter::EEncounterType::eNone;

    _pathNorth = false;
    _pathSouth = false;
    _pathEast = false;
    _pathWest = false;

    _seen = false;
}

void CDungeonRoomNoRoom::setSeen(const bool)
{
}

bool CDungeonRoomNoRoom::isSpecialRoom() const
{
    return true;
}

bool CDungeonRoomNoRoom::isEmptyRoom() const
{
    return true;
}
