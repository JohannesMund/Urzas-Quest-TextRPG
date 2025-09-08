#include "cfish.h"

#include <nlohmann/json.hpp>

CFish::CFish() : CFish(0, 0)
{
}

CFish::CFish(const unsigned int rodLevel, const unsigned int boatLevel) :
    CFish(FishingVillageRessources::getRandomRarity(rodLevel, boatLevel))
{
}

CFish::CFish(const FishingVillageRessources::EFishLevel level) : CItem("CFish")
{
    _value = FishingVillageRessources::getFishPrice(level);
    _name = FishingVillageRessources::getFish(level);

    _isSellable = false;
    _isBuyable = false;

    _fishLevel = level;
    _description =
        "A beautiful fish, caught by yourself. Can be sold for money. Money can be exchanged for goods and services.";
}

FishingVillageRessources::EFishLevel CFish::fishLevel() const
{
    return _fishLevel;
}

CItem::ItemFilter CFish::fishFilter()
{
    return [](const CItem* item) { return dynamic_cast<const CFish*>(item) != nullptr; };
}

CItem::ItemFilter CFish::fishRarityFilter(const FishingVillageRessources::EFishLevel level)
{
    return [level](const CItem* item)
    {
        auto fish = dynamic_cast<const CFish*>(item);
        if (fish != nullptr)
        {
            return fish->fishLevel() == level;
        }
        return false;
    };
}

nlohmann::json CFish::save() const
{
    nlohmann::json o = CItem::save();
    o["fishLevel"] = _fishLevel;
    return o;
}
