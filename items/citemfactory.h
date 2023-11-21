#pragma once

#include "ressources.h"

#include <functional>
#include <string>
#include <vector>

class CItem;

class CItemFactory
{
    friend class CGameManagement;
    friend class CInventory;

public:
    CItem* makeLootItem();
    CItem* makeAwesomneItem();
    CItem* makeShopItem();

    CItem* makeShopEquipment(const unsigned int playerLevel);
    CItem* makeEquipment(const Ressources::Items::EType type, const Ressources::Items::EQuality quality);

    using LootItemGeneratorFunction = std::function<CItem*()>;

    void registerLootItemGenerator(const std::string_view& moduleName,
                                   LootItemGeneratorFunction generatorFunction,
                                   const unsigned int dropRate);
    void unregisterLootItemGeneratorByName(const std::string_view& moduleName);

private:
    CItemFactory()
    {
    }

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

    struct LootItemGenerator
    {
        std::string moduleName;
        LootItemGeneratorFunction lootGenerator;
        unsigned int dropRate;

        static std::function<bool(const LootItemGenerator&)> nameFilter(const std::string_view& moduleName)
        {
            return [moduleName](const LootItemGenerator& generator)
            { return generator.moduleName.compare(moduleName) == 0; };
        }
    };

    std::vector<LootItemGenerator> _lootGenerators;
};
