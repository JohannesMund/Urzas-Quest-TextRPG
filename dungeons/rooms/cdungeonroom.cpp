#include "cdungeonroom.h"
#include "cgamemanagement.h"

CDungeonRoom::CDungeonRoom()
{
    _encounterPossible = true;
    _taskPossible = true;
}

void CDungeonRoom::execute()
{
    if (_encounterPossible && !hasTask())
    {
        CGameManagement::getInstance()->executeRandomEncounter(CEncounter::eDungeon, _moduleName);
    }

    CRoom::execute();
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
