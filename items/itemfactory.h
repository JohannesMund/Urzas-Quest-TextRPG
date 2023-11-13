#pragma once

#include "citem.h"
#include "ressources.h"

namespace ItemFactory
{
enum class EItemType
{
    eHealingPotionS,
    eHealingPotionM,
    eHealingPotionL,
    eHealingPotionXL,

    eBombS,
    eBombM,
    eBombL,
    eBombXL,

    ePhoenixFeather,
    eHeartContainer,

    eJunkItem,

    eUrzasGlasses
};

CItem* makeItem(const EItemType tp);
CItem* makeShopItem();
CItem* makeAwesomneItem();

CItem* makeEquipment(const Ressources::Items::EType type, const Ressources::Items::EQuality quality);

} // namespace ItemFactory
