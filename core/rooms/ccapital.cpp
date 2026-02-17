#include "ccapital.h"
#include "colorize.h"
#include "console.h"
#include "ressources.h"

CCapital::CCapital() : CTown(TagNames::Room::capital)
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

std::string CCapital::translatorModuleName() const
{
    return std::string();
}

nlohmann::json CCapital::save() const
{
    nlohmann::json o = CTown::save();
    o[TagNames::Room::isOpen] = _open;
    return o;
}

void CCapital::load(const nlohmann::json& json)
{
    _seen = json.value<bool>(TagNames::Room::isOpen, false);
    CTown::load(json);
}

char CCapital::getMapSymbol() const
{
    return CTown::getMapSymbol();
}
