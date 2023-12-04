#include "cfield.h"
#include "cgamemanagement.h"

CField::CField() : CRoom()
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

char CField::getMapSymbol() const
{
    return ' ';
}
