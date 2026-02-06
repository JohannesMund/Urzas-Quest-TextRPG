#pragma once

#include "ressources.h"

#include <functional>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <vector>

class CItem;
class CSandwich;
class CItemFactory
{
    friend class CGameManagement;
    friend class CInventory;

public:
    CItem* makeLootItem();
    CItem* makeAwesomneItem();
    CItem* makeShopItem() const;
    CSandwich* sandwichMaker() const;

    CItem* makeShopEquipment(const unsigned int playerLevel);
    CItem* makeEquipment(const Ressources::Items::EType type, const Ressources::Items::EQuality quality);

    using ItemGeneratorFunction = std::function<CItem*()>;

    void registerLootItemGenerator(const std::string_view& moduleName,
                                   ItemGeneratorFunction generatorFunction,
                                   const unsigned int dropRate);
    void unregisterLootItemGeneratorByName(const std::string_view& moduleName);

    void registerShopItemGenerator(const std::string_view& moduleName,
                                   ItemGeneratorFunction generatorFunction,
                                   const unsigned int dropRate);
    void unregisterShopItemGeneratorByName(const std::string_view& moduleName);

    static CItem* loadItemFromSavGame(const nlohmann::json& json);

    static std::string coreTr(const std::string_view& textId);

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
    };
    static CItem* generateItem(const EItemType tp);
    static CItem* generateShopItem();

    struct ItemGenerator
    {
        std::string moduleName;
        ItemGeneratorFunction generatorFunction;
        unsigned int dropRate;

        static std::function<bool(const ItemGenerator&)> nameFilter(const std::string_view& moduleName)
        {
            return [moduleName](const ItemGenerator& generator)
            { return generator.moduleName.compare(moduleName) == 0; };
        }
    };

    using ItemGeneratorList = std::vector<ItemGenerator>;

    ItemGeneratorList _lootGenerators;
    ItemGeneratorList _shopGenerators;

    CItem* itemFromGeneratorList(const ItemGeneratorList& list, const ItemGeneratorFunction& defaultGenerator) const;
};
