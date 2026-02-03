#include "cfish.h"
#include "../moduleressources.h"

#include <nlohmann/json.hpp>

CFish::CFish() : CFish(0, 0)
{
}

CFish::CFish(const unsigned int rodLevel, const unsigned int boatLevel) :
    CFish(FishingVillage::getRandomRarity(rodLevel, boatLevel))
{
}

CFish::CFish(const FishingVillage::EFishLevel level) : CItem(TagNames::FishingVille::fish)
{
    _value = FishingVillage::getFishPrice(level);
    _name = FishingVillage::getFish(level);

    _isSellable = false;
    _isBuyable = false;

    _fishLevel = level;
    _description =
        "A beautiful fish, caught by yourself. Can be sold for money. Money can be exchanged for goods and services.";
}

FishingVillage::EFishLevel CFish::fishLevel() const
{
    return _fishLevel;
}

CItem::ItemFilter CFish::fishFilter()
{
    return [](const CItem* item) { return dynamic_cast<const CFish*>(item) != nullptr; };
}

CItem::ItemFilter CFish::fishRarityFilter(const FishingVillage::EFishLevel level)
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

void CFish::load(const nlohmann::json& json)
{
    _fishLevel = json.value<FishingVillage::EFishLevel>(TagNames::FishingVille::fishLevel,
                                                                  FishingVillage::EFishLevel::eCommon);
}
