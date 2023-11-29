#include "cdungeonroom.h"
#include "cgamemanagement.h"

CDungeonRoom::CDungeonRoom() : CRoom()
{
    _encounterType = CEncounter::EEncounterType::eDungeon;
    _isRandomTaskPossible = true;
}

void CDungeonRoom::setDescription(const std::string_view& description)
{
    _description = description;
}

void CDungeonRoom::setModuleName(const std::string_view& moduleName)
{
    _moduleName = moduleName;
}

bool CDungeonRoom::isSpecialRoom() const
{
    return false;
}

char CDungeonRoom::getMapSymbol() const
{
    return ' ';
}
