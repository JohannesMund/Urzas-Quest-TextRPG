#pragma once

#include "citem.h"

#include <map>
#include <optional>
#include <string>
#include <vector>

class CEnemy;
class CEquipment;
class CJunkItem;
class CItemFactory;
class CInventory
{
    friend class CGameManagement;

public:
    using CompressedItem = std::pair<unsigned int, CItem*>;
    using CompressedItemMap = std::vector<CompressedItem>;
    using ItemList = std::vector<CItem*>;
    using EquipmentList = std::vector<CEquipment*>;
    using EnhancableEquipmentList = std::vector<CEquipment*>;

    using JunkItemList = std::vector<CJunkItem*>;

    enum class Scope
    {
        eNone,
        eView,
        eList,
        eInventory,
        eBattle,
        eDeath
    };

    bool hasItem(const std::string& name);
    void addItem(CItem* item);

    void addLootItem();
    void addAwesomneItem();
    void addShopItem();

    void removeItem(CItem* item);
    void removeItem(const std::string& name);
    void removeItem(CItem::ItemFilter filter);

    void print(const Scope& scope = Scope::eNone);

    //    ItemList getItems(std::fun)

    ItemList getItemsWithBattleEffect() const;
    void useBattleEffect(CItem* item, CEnemy* enemy);

    ItemList getItemsWithDurableBattleEffect() const;
    void useDurableBattleEffect(CItem* item, CEnemy* enemy, bool& endRound);

    ItemList getItemsWithShieldingAction() const;
    unsigned int useShieldingAction(CItem* item, const int damage);

    ItemList getItemsWithDeathEffect() const;
    void useDeathAction(CItem* item);

    ItemList getItemsByFilter(CItem::ItemFilter filter) const;
    CompressedItemMap getCompressedItemMap(CItem::ItemFilter filter) const;

    bool hasItem(CItem::ItemFilter filter) const;

    JunkItemList getJunkItems() const;
    EquipmentList getEquipment() const;
    EquipmentList getEnhancableEquipment() const;

    CompressedItemMap getSellableItems() const;

    std::optional<CItem*> selectItemFromInventory(const Scope& scope);

private:
    CInventory(CItemFactory* itemFactory);
    ~CInventory();

    std::string printInventoryNav() const;

    CompressedItemMap getInventoryCompressedForScope(const Scope& scope) const;

    static bool usableInScope(const CItem* item, const Scope& scope);

    void printUsableItems(const Scope& scope);
    void printViewableItems();

    void viewItem(CItem* item);

    CItem* getItem(const unsigned int index);
    ItemList _inventory;
    CItemFactory* _itemFactory;
};
