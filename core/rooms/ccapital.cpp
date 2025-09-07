#include "ccapital.h"
#include "colorize.h"
#include "console.h"
#include "ressources.h"

CCapital::CCapital() : CTown("CCaptial")
{
    auto city = Ressources::Rooms::getCapital();
    _description = city.second;
    _name = city.first;

    _encounterType = CEncounter::EEncounterType::eNone;
    _isRandomTaskPossible = false;
}

void CCapital::execute()
{
    if (_open)
    {
        return CTown::execute();
    }
    else
    {
        Console::printLn(_name, Console::EAlignment::eCenter);
        Console::br();
        CRoom::execute();

        Console::printLn(Ressources::Rooms::getCapitalRejection());
    }
}

std::string CCapital::bgColor() const
{
    return CC::bgYellow();
}

std::string CCapital::fgColor() const
{
    return CTown::fgColor();
}

CMap::RoomFilter CCapital::capitalFilter()
{
    return [](const CRoom* room) { return dynamic_cast<const CCapital*>(room) != nullptr; };
}

nlohmann::json CCapital::save() const
{
    nlohmann::json o = CTown::save();
    o["open"] = _open;
    return o;
}

char CCapital::getMapSymbol() const
{
    return CTown::getMapSymbol();
}
