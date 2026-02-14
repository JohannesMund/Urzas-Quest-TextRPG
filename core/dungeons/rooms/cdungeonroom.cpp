#include "cdungeonroom.h"
#include "cgamemanagement.h"

CDungeonRoom::CDungeonRoom() : CRoom("CDungeonRoom")
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

std::string CDungeonRoom::translatorModuleName() const
{
    return std::string();
}

char CDungeonRoom::getMapSymbol() const
{
    return ' ';
}
