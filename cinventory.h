#pragma once

#include "citem.h"

#include <map>
#include <optional>
#include <string>
#include <vector>

class CEnemy;
class CEquipment;
class CJunkItem;
class CInventory
{
public:
    using CompressedItem = std::pair<unsigned int, CItem*>;
    using CompressedItemMap = std::vector<CompressedItem>;
    using ItemList = std::vector<CItem*>;
    using EquipmentList = std::vector<CEquipment*>;
    using EnhancableEquipmentList = std::vector<CEquipment*>;

    using JunkItemList = std::vector<CJunkItem*>;

    CInventory();
    ~CInventory();

    enum class Scope
    {
        eNone,
        eView,
        eList,
        eInventory,
        eBattle,
        eDeath
    };

    bool hasItem(const std::string_view& name);
    void addItem(CItem* item);

    void removeItem(CItem* item);
    void removeItem(const std::string_view& name);

    void print(const Scope& scope = Scope::eNone);

    ItemList getItemsWithBattleEffect() const;
    void useBattleEffect(CItem* item, CEnemy* enemy);

    ItemList getItemsWithDurableBattleEffect() const;
    void useDurableBattleEffect(CItem* item, CEnemy* enemy, bool& endRound);

    ItemList getItemsWithShieldingAction() const;
    unsigned int useShieldingAction(CItem* item, const int damage);

    ItemList getItemsWithDeathEffect() const;
    void useDeathAction(CItem* item);

    JunkItemList getJunkItems() const;
    EquipmentList getEquipment() const;
    EquipmentList getEnhancableEquipment() const;

    CompressedItemMap getSellableItems() const;

    std::optional<CItem*> selectItemFromInventory(const Scope& scope);

private:
    std::string printInventoryNav() const;

    CompressedItemMap getCompressedItemMap(std::function<bool(const CItem*)> filter) const;
    CompressedItemMap getInventoryCompressedForScope(const Scope& scope) const;

    static bool usableInScope(const CItem* item, const Scope& scope);

    void printUsableItems(const Scope& scope);
    void printViewableItems();

    void viewItem(CItem* item);

    CItem* getItem(const unsigned int index);
    ItemList _inventory;
};
