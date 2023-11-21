#pragma once

#include "ressources.h"

#include <functional>
#include <string>
#include <vector>

class CItem;

class CItemFactory
{
    friend class CGameManagement;

public:
    using LootItemGeneratorFunction = std::function<CItem*()>;

    CItem* makeLootItem();

    CItem* makeShopEquipment(const unsigned int playerLevel);
    CItem* makeAwesomneItem();

    CItem* makeShopItem();
    CItem* makeEquipment(const Ressources::Items::EType type, const Ressources::Items::EQuality quality);

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
