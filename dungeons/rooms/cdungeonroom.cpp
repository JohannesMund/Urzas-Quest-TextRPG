#include "cdungeonroom.h"
#include "cgamemanagement.h"

CDungeonRoom::CDungeonRoom() : CRoom()
{
    _encounterType = CEncounter::EEncounterType::eDungeon;
    _isTaskPossible = true;
}

std::string CDungeonRoom::mapSymbol() const
{
    return CRoom::mapSymbol();
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
