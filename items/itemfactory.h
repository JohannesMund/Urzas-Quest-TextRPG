#pragma once

#include "ressources.h"

class CItem;

namespace ItemFactory
{

CItem* makeLootItem();

CItem* makeShopEquipment(const unsigned int playerLevel);
CItem* makeAwesomneItem();

CItem* makeShopItem();
CItem* makeEquipment(const Ressources::Items::EType type, const Ressources::Items::EQuality quality);

} // namespace ItemFactory
