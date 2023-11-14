#pragma once

#include "cinventory.h"
#include "ctownmodule.h"

#include <vector>

class CItem;
class CShop : public CTownModule
{
public:
    CShop();
    ~CShop();
    void execute();

private:
    void sellJunk(CInventory::JunkItemList& junkItems);
    void buyItems();
    void sellItems();
    void buyItem(CItem* item);
    void sellItem(CItem* item, const unsigned int amount);

    void replaceShopItems();
    std::vector<CItem*> _shopItems;

    unsigned int _playerLevel;
};
