#include "cfield.h"
#include "cgamemanagement.h"
#include "cgamestateobject.h"

CField::CField(const std::string_view& objectName) : CRoom(objectName)
{
    _encounterType = CEncounter::EEncounterType::eField;
}

std::string CField::fgColor() const
{
    return CC::fgWhite();
}

std::string CField::bgColor() const
{
    return "\33[48;5;22m";
}

CMap::RoomFilter CField::fieldFilter()
{
    return [](const CRoom* room) { return dynamic_cast<const CField*>(room) != nullptr; };
}

std::string CField::translatorModuleName() const
{
    return std::string();
}

char CField::getMapSymbol() const
{
    return ' ';
}
