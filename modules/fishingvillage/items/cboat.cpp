#include "cboat.h"
#include "colorize.h"

#include <format>

CBoat::CBoat() : CEquipment(Ressources::Items::EType::eOther, Ressources::Items::EQuality::eGood, "CBoat")
{
    _namesByLevel = {
        std::format("{}Fragile {}Nutshell{}", CC::fgLightRed(), CC::fgLightYellow(), CC::ccReset()),
        std::format("{}Tiny {}Rowboat{}", CC::fgLightRed(), CC::fgLightYellow(), CC::ccReset()),
        std::format("{}Row{}boat{}", CC::fgLightRed(), CC::fgLightYellow(), CC::ccReset()),
        std::format("{}Fishing {}Boat{}", CC::fgLightRed(), CC::fgLightYellow(), CC::ccReset()),
        std::format("Godly {}Sh{}ip{} of the Dragon Fish", CC::fgLightRed(), CC::fgLightYellow(), CC::ccReset())};
    _description = "This is your boat. Your life depends on this thing, when you are out on the open sea.";
}

std::string CBoat::typeName() const
{
    return "Boat";
}

CItem::ItemFilter CBoat::boatFilter()
{
    return [](const CItem* item) { return dynamic_cast<const CBoat*>(item) != nullptr; };
}

CItem::ItemFilter CBoat::equipmentTypeFilter() const
{
    return boatFilter();
}

unsigned int CBoat::upgradeCost() const
{
    return CEquipment::upgradeCost() * 5;
}
