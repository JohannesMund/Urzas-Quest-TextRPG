#include "cfishingrod.h"
#include "colorconsole.h"
#include "ressources.h"

#include <format>

CFishingRod::CFishingRod() : CEquipment(Ressources::Items::EType::eOther, Ressources::Items::EQuality::eGood)
{
    _namesByLevel = {
        std::format(
            "{}Fishing {}Line on a {}Stick{}", CC::fgLightCyan(), CC::fgLightGray(), CC::fgYellow(), CC::ccReset()),
        std::format("Cheap {}Fi{}shing {}Rod{}", CC::fgLightCyan(), CC::fgLightGray(), CC::fgYellow(), CC::ccReset()),
        std::format("{}Fi{}shing {}Rod{}", CC::fgLightCyan(), CC::fgLightGray(), CC::fgYellow(), CC::ccReset()),
        std::format("Strong {}Fi{}shing {}Rod{}", CC::fgLightCyan(), CC::fgLightGray(), CC::fgYellow(), CC::ccReset()),
        std::format("Godly {}Fi{}shing {}Rod{} of the Dragon Fish",
                    CC::fgLightCyan(),
                    CC::fgLightGray(),
                    CC::fgYellow(),
                    CC::ccReset())};
    _description = "It's a fishing rod. used for fishing, and... no, fishing only";
}

std::string CFishingRod::typeName() const
{
    return "Fishing Rod";
}

CItem::ItemFilter CFishingRod::fishingRodFilter()
{
    return [](const CItem* item) { return dynamic_cast<const CFishingRod*>(item) != nullptr; };
}

CItem::ItemFilter CFishingRod::equipmentTypeFilter() const
{
    return fishingRodFilter();
}

unsigned int CFishingRod::upgradeCost() const
{
    return CEquipment::upgradeCost() * 2;
}
