#pragma once

#include "citem.h"
#include "fishingvillage/moduleressources.h"

class CFish : public CItem
{
public:
    CFish();
    CFish(const unsigned int rodLevel, const unsigned int boatLevel);
    CFish(const FishingVillage::EFishLevel level);

    FishingVillage::EFishLevel fishLevel() const;

    static CItem::ItemFilter fishFilter();
    static CItem::ItemFilter fishRarityFilter(const FishingVillage::EFishLevel level);

protected:
    virtual nlohmann::json save() const override;
    virtual void load(const nlohmann::json& json) override;

private:
    FishingVillage::EFishLevel _fishLevel;
};
