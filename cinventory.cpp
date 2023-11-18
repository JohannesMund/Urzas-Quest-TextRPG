#include "cinventory.h"
#include "cequipment.h"
#include "cjunkitem.h"
#include "cmenu.h"
#include "console.h"

#include <algorithm>
#include <format>
#include <ranges>
#include <string>
#include <utility>

CInventory::CInventory()
{
}

CInventory::~CInventory()
{
    for (auto i : _inventory)
    {
        delete i;
    }
    _inventory.clear();
}

bool CInventory::hasItem(const std::string_view& name)
{
    return std::find_if(_inventory.begin(), _inventory.end(), CItem::nameFilter(name)) != _inventory.end();
}

void CInventory::addItem(CItem* item)
{
    if (CEquipment::isEquipment(item))
    {
        auto equipment = dynamic_cast<CEquipment*>(item);

        auto it = std::find_if(_inventory.begin(), _inventory.end(), equipment->equipmentTypeFilter());
        if (it != _inventory.end())
        {
            Console::printLn(std::format(
                "Your already have a {} do you want to replace it with {}", equipment->typeName(), equipment->name()));

            if (CMenu::executeYesNoMenu() == CMenu::no())
            {
                Console::printLn(std::format("You decide to keep {} and reject {}.", (*it)->name(), item->name()));
                delete item;
                return;
            }

            Console::printLn(std::format("You decide to throw away you {}.", (*it)->name()));

            delete *it;
            _inventory.erase(it);
        }
    }

    Console::printLn(std::format("You optained {}", item->name()));
    _inventory.push_back(item);
}

void CInventory::removeItem(CItem* item)
{
    removeItem(item->name());
}
void CInventory::removeItem(const std::string_view& name)
{
    auto found = std::find_if(_inventory.begin(), _inventory.end(), CItem::nameFilter(name));
    if (found != _inventory.end())
    {
        delete *found;
        _inventory.erase(found);
    }
}

void CInventory::print(const Scope& scope)
{
    Console::printLn("You look through your backpack and find the following:");
    selectItemFromInventory(scope);
    CMenu::Action input;
    do
    {
        Console::hr();
        CMenu menu;
        menu.addMenuGroup({menu.createAction("Use Item"), menu.createAction("View Item")}, {CMenu::exit()});
        input = menu.execute();

        if (input.key == 'u')
        {
            printUsableItems(Scope::eInventory);
        }
        if (input.key == 'v')
        {
            printViewableItems();
        }
    } while (input != CMenu::exit());
}

CInventory::ItemList CInventory::getItemsWithBattleEffect() const
{
    ItemList itemsWithBattleEffect;
    std::copy_if(
        _inventory.begin(), _inventory.end(), std::back_inserter(itemsWithBattleEffect), CItem::battleEffectFilter());
    return itemsWithBattleEffect;
}

void CInventory::useBattleEffect(CItem* item, CEnemy* enemy)
{
    if (item == nullptr)
    {
        return;
    }
    item->battleEffect(enemy);
    if (item->isConsumable())
    {
        removeItem(item);
    }
}

CInventory::ItemList CInventory::getItemsWithDurableBattleEffect() const
{
    ItemList itemsWithBattleEffect;
    std::copy_if(_inventory.begin(),
                 _inventory.end(),
                 std::back_inserter(itemsWithBattleEffect),
                 CItem::durableBattleEffectFilter());
    return itemsWithBattleEffect;
}

void CInventory::useDurableBattleEffect(CItem* item, CEnemy* enemy, bool& endRound)
{
    if (item == nullptr)
    {
        return;
    }

    item->battleBuff(enemy, endRound);
    if (item->isConsumable())
    {
        removeItem(item);
    }
}

CInventory::ItemList CInventory::getItemsWithShieldingAction() const
{
    ItemList itemsWithShieldingAction;
    std::copy_if(_inventory.begin(),
                 _inventory.end(),
                 std::back_inserter(itemsWithShieldingAction),
                 CItem::shieldingActionFilter());
    return itemsWithShieldingAction;
}

unsigned int CInventory::useShieldingAction(CItem* item, const int damage)
{
    if (item == nullptr)
    {
        return damage;
    }
    return item->shield(damage);
}

CInventory::ItemList CInventory::getItemsWithDeathEffect() const
{
    ItemList itemsWithDeathEffect;
    std::copy_if(
        _inventory.begin(), _inventory.end(), std::back_inserter(itemsWithDeathEffect), CItem::deathEffectFilter());
    return itemsWithDeathEffect;
}

void CInventory::useDeathAction(CItem* item)
{
    if (item == nullptr)
    {
        return;
    }
    item->deathEffect();
    if (item->isConsumable())
    {
        removeItem(item);
    }
}

CInventory::ItemList CInventory::getItemsByFilter(CItem::ItemFilter filter) const
{
    ItemList items;
    for (const auto& item : _inventory | std::views::filter(filter))
    {
        items.push_back(item);
    }
    return items;
}

CInventory::JunkItemList CInventory::getJunkItems() const
{
    JunkItemList junkItems;
    for (const auto item : _inventory | std::views::filter(CJunkItem::junkItemFilter()))
    {
        auto junkItem = dynamic_cast<CJunkItem*>(item);
        if (junkItem != nullptr)
        {
            junkItems.push_back(junkItem);
        }
    }

    return junkItems;
}

CInventory::EquipmentList CInventory::getEquipment() const
{
    EquipmentList equipmentItems;
    for (const auto item : _inventory | std::views::filter(CEquipment::equipmentFilter()) |
                               std::views::transform(CEquipment::equipmentTransformation()))
    {
        equipmentItems.push_back(item);
    }
    return equipmentItems;
}

CInventory::EquipmentList CInventory::getEnhancableEquipment() const
{
    EquipmentList equipmentItems;
    for (const auto item : _inventory | std::views::filter(CEquipment::enhancableEquipmentFilter()) |
                               std::views::transform(CEquipment::equipmentTransformation()))
    {
        equipmentItems.push_back(item);
    }
    return equipmentItems;
}

CInventory::CompressedItemMap CInventory::getSellableItems() const
{
    return getCompressedItemMap([](const CItem* item) { return item->isSellable(); });
}

CInventory::CompressedItemMap CInventory::getInventoryCompressedForScope(const Scope& scope) const
{
    return getCompressedItemMap([&scope](const CItem* item)
                                { return usableInScope(item, scope) || scope == Scope::eList; });
}

CInventory::CompressedItemMap CInventory::getCompressedItemMap(CItem::ItemFilter filter) const
{
    CompressedItemMap itemMap;
    for (auto item : _inventory)
    {
        if (!filter(item))
        {
            continue;
        }

        auto foundItem = std::find_if(itemMap.begin(),
                                      itemMap.end(),
                                      [&item](const std::pair<unsigned int, CItem*>& p) -> bool
                                      { return p.second->name().compare(item->name()) == 0; });
        if (foundItem == itemMap.end())
        {
            auto count =
                std::count_if(_inventory.begin(),
                              _inventory.end(),
                              [&item](const CItem* it) -> bool { return it->name().compare(item->name()) == 0; });

            itemMap.push_back(std::make_pair(count, item));
        }
    }
    return itemMap;
}

bool CInventory::hasItem(CItem::ItemFilter filter) const
{
    return std::find_if(_inventory.begin(), _inventory.end(), filter) != _inventory.end();
}

std::optional<CItem*> CInventory::selectItemFromInventory(const Scope& scope)
{
    auto itemMap = getInventoryCompressedForScope(scope);
    std::vector<CItem*> usableItems;
    for (auto item : itemMap)
    {
        if (scope == Scope::eList)
        {
            Console::printLn(std::format("    {} (x{})", item.second->name(), item.first));
        }
        else
        {
            usableItems.push_back(item.second);
            Console::printLn(std::format("[{:3}] {} (x{})", usableItems.size(), item.second->name(), item.first));
        }
    }

    if (usableItems.size())
    {
        auto item = Console::getNumberInputWithEcho(1, usableItems.size());
        if (item.has_value())
        {
            return usableItems.at(*item - 1);
        }
    }
    return {};
}

bool CInventory::usableInScope(const CItem* item, const Scope& scope)
{
    switch (scope)
    {
    case Scope::eNone:
    default:
    case Scope::eList:
        return false;
    case Scope::eView:
        return true;
    case Scope::eInventory:
        return item->isUsableFromInventory();
    case Scope::eBattle:
        return item->isUsableFromBattle();
    case Scope::eDeath:
        return item->hasDeathEffect();
    }
}

void CInventory::printUsableItems(const Scope& scope)
{
    Console::printLn("Select item to use");
    Console::hr();
    auto item = selectItemFromInventory(scope);
    if (item.has_value())
    {
        Console::hr();
        Console::printLn(std::format("You decide to use: {}", (*item)->name()));
        (*item)->useFromInventory();
        if ((*item)->isConsumable())
        {
            removeItem(*item);
        }
    }
}

void CInventory::printViewableItems()
{
    Console::printLn("Select item to view");
    Console::hr();
    auto item = selectItemFromInventory(Scope::eView);
    if (item.has_value())
    {
        viewItem(*item);
    }
}

void CInventory::viewItem(CItem* item)
{
    if (item == nullptr)
    {
        return;
    }
    item->view();
}

CItem* CInventory::getItem(const unsigned int index)
{
    if (_inventory.size() < index)
    {
        return nullptr;
    }
    return _inventory.at(index);
}
