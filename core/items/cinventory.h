#pragma once

#include "cgamestateobject.h"
#include "citem.h"

#include <map>
#include <optional>
#include <string>
#include <vector>

class CEnemy;
class CEquipment;
class CJunkItem;
class CItemFactory;
class CInventory : public CGameStateObject
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

    template <typename T>
    std::optional<T*> takeFirstItem(CItem::ItemFilter filter)
    {
        auto it = std::find_if(_inventory.begin(), _inventory.end(), filter);
        if (it != _inventory.end())
        {
            auto item = static_cast<T*>(*it);
            if (item == nullptr)
            {
                return {};
            }

            it = std::remove(_inventory.begin(), _inventory.end(), *it);
            _inventory.erase(it, _inventory.end());
            return item;
        }
        return {};
    }

    void print(const Scope& scope = Scope::eNone);

    ItemList getItemsWithBattleEffect() const;
    void useBattleEffect(CItem* item, CEnemy* enemy);

    ItemList getItemsWithDurableBattleEffect() const;
    void useDurableBattleEffect(CItem* item, CEnemy* enemy, bool& endRound);

    ItemList getItemsWithShieldingAction() const;
    unsigned int useShieldingAction(CItem* item, const int damage);

    ItemList getItemsWithDeathEffect() const;
    void useDeathAction(CItem* item);

    ItemList getItemsByFilter(CItem::ItemFilter filter) const;
    template <typename T>
    std::optional<T*> getFirstItemByFilter(CItem::ItemFilter filter) const
    {
        const auto items = getItemsByFilter(filter);
        if (items.size() == 0)
        {
            return {};
        }

        auto item = static_cast<T*>(items.at(0));
        if (item == nullptr)
        {
            return {};
        }

        return item;
    }

    CompressedItemMap getCompressedItemMap(CItem::ItemFilter filter) const;

    bool hasItem(CItem::ItemFilter filter) const;

    JunkItemList getJunkItems() const;
    EquipmentList getEquipment() const;
    EquipmentList getEnhancableEquipment() const;

    CompressedItemMap getSellableItems() const;

    std::optional<CItem*> selectItemFromInventory(const Scope& scope);

protected:
    virtual std::string translatorObjectName() const override;
    virtual std::string translatorModuleName() const override;

private:
    CInventory(CItemFactory* itemFactory);
    ~CInventory();

    std::string printInventoryNav() const;

    CompressedItemMap getInventoryCompressedForScope(const Scope& scope) const;

    static bool usableInScope(const CItem* item, const Scope& scope);

    void printUsableItems(const Scope& scope);
    void printViewableItems();

    void viewItem(CItem* item);

    virtual nlohmann::json save() const override;
    void load(const nlohmann::json&) override;

    CItem* getItem(const unsigned int index);
    ItemList _inventory;
    CItemFactory* _itemFactory;
};
