#include "cfield.h"
#include "cgamemanagement.h"

CField::CField() : CRoom()
{
    _encounterType = CEncounter::EEncounterType::eField;
}

std::string CField::mapSymbol() const
{
    return CRoom::mapSymbol();
}
