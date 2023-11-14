#include "cshop.h"
#include "cgamemanagement.h"
#include "cjunkitem.h"
#include "cmenu.h"
#include "console.h"
#include "itemfactory.h"

#include <algorithm>
#include <format>
#include <map>

CShop::CShop()
{
    replaceShopItems();
}

CShop::~CShop()
{
    for (auto i : _shopItems)
    {
        if (i != nullptr)
        {
            delete i;
        }
    }
    _shopItems.clear();
}

void CShop::execute()
{
    if (CGameManagement::getPlayerInstance()->level() != _playerLevel)
    {
        replaceShopItems();
    }

    CMenu::Action input;
    do
    {
        Console::cls();
        Console::printLn(
            std::format("The shop of {} looks like any shop in any generic D&D game. Even the clerc looks "
                        "stereotypical. The shop is filled with junk,but who knows, maybe you will find something cool "
                        "here? Or make some food money selling your precious valuables?",
                        _cityName));
        Console::hr();

        CMenu menu;
        auto junkItems = CGameManagement::getInventoryInstance()->getJunkItems();
        if (junkItems.size())
        {
            int value = 0;
            for (auto j : junkItems)
            {
                if (j->isSellable())
                {
                    value += j->value();
                }
            }
            menu.addMenuGroup({menu.createAction(std::format("Sell your Junk ({} Gold)", value), 'j')});
        }

        menu.addMenuGroup({menu.createAction("Buy items"), menu.createAction("Sell items")}, {CMenu::exit()});
        input = menu.execute();
        if (input.key == 'j')
        {
            sellJunk(junkItems);
        }
        if (input.key == 'b')
        {
            buyItems();
        }
        if (input.key == 's')
        {
            sellItems();
        }

    } while (input != CMenu::exit());
}

void CShop::sellJunk(CInventory::JunkItemList& junkItems)
{
    for (auto j : junkItems)
    {
        if (j->isSellable())
        {
            CGameManagement::getPlayerInstance()->addGold(j->value());
            CGameManagement::getInventoryInstance()->removeItem(j);
        }
    }
    Console::confirmToContinue();
}

void CShop::buyItems()
{
    Console::printLn("Browsing through the shop, you identify some items you might want to buy:");

    std::vector<CItem*> buyableItems;
    for (auto i : _shopItems)
    {
        if (i->buyValue() <= CGameManagement::getPlayerInstance()->gold())
        {
            buyableItems.push_back(i);
            Console::printLn(std::format("[{:3}] {} ({} Gold)", buyableItems.size(), i->name(), i->buyValue()));
        }
        else
        {
            Console::printLn(std::format("[   ] {} ({} Gold)", i->name(), i->buyValue()));
        }
    }

    if (buyableItems.size())
    {
        auto input = Console::getNumberInputWithEcho(1, buyableItems.size());
        if (input.has_value())
        {
            buyItem(buyableItems.at(*input - 1));
        }
    }
}

void CShop::sellItems()
{
    auto sellableItems = CGameManagement::getInventoryInstance()->getSellableItems();
    if (sellableItems.size() == 0)
    {
        Console::printLn("You look through your backpack and find, that you don't have any valuables to sell");
        Console::confirmToContinue();
        return;
    }

    Console::printLn("You look through your backpack for valuables to sell:");
    auto index = 0;

    for (const auto& item : sellableItems)
    {
        index++;
        Console::printLn(
            std::format("[{:3}] {} x{} ({} Gold)", index, item.second->name(), item.first, item.second->value()));
    }

    auto input = Console::getNumberInputWithEcho(1, sellableItems.size());
    if (!input.has_value())
    {
        return;
    }

    auto item = sellableItems.at(*input - 1);

    Console::printLn("How Many?");

    auto amount = Console::getNumberInputWithEcho(1, item.first);
    if (!amount.has_value())
    {
        return;
    }

    sellItem(item.second, *amount);
    Console::confirmToContinue();
}

void CShop::buyItem(CItem* item)
{
    CGameManagement::getInventoryInstance()->addItem(item);
    CGameManagement::getPlayerInstance()->addGold(item->buyValue() * -1);

    auto it = std::find_if(_shopItems.begin(), _shopItems.end(), CItem::nameFilter(item->name()));
    if (it != _shopItems.end())
    {
        _shopItems.erase(it);
        _shopItems.push_back(ItemFactory::makeShopItem());
    }
    Console::confirmToContinue();
}

void CShop::sellItem(CItem* item, const unsigned int amount)
{
    auto value = item->value();
    auto name = item->name();

    for (int i = 0; i < amount; i++)
    {
        CGameManagement::getPlayerInstance()->addGold(value);
        CGameManagement::getInventoryInstance()->removeItem(name);
    }
}

void CShop::replaceShopItems()
{
    _playerLevel = CGameManagement::getPlayerInstance()->level();
    for (auto i : _shopItems)
    {
        delete i;
    }
    _shopItems.clear();

    for (int i = 0; i < 5; i++)
    {
        _shopItems.push_back(ItemFactory::makeShopItem());
    }
}
