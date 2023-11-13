#pragma once

#include "ressources.h"

class CItem;

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
CItem* makeShopEquipment(const unsigned int playerLevel);
CItem* makeAwesomneItem();

CItem* makeShopItem();
CItem* makeEquipment(const Ressources::Items::EType type, const Ressources::Items::EQuality quality);

} // namespace ItemFactory
