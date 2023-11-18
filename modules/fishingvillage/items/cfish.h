#pragma once

#include "citem.h"
#include "fishingvillage/moduleressources.h"

class CFish : public CItem
{
public:
    CFish();
    CFish(const unsigned int rodLevel, const unsigned int boatLevel);
    CFish(const FishingVillageRessources::EFishLevel level);

    FishingVillageRessources::EFishLevel fishLevel() const;

    static CItem::ItemFilter fishFilter();
    static CItem::ItemFilter fishRarityFilter(const FishingVillageRessources::EFishLevel level);

private:
    FishingVillageRessources::EFishLevel _fishLevel;
};
