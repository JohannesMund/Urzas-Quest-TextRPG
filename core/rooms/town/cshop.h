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
    virtual void execute() override;
    virtual CMenuAction townModuleNav(CMenu& menu) const override;

private:
    void sellJunk(CInventory::JunkItemList& junkItems);
    void buyItems();
    void sellItems();
    void buyItem(CItem* item);
    void sellItem(CItem* item, const unsigned int stock);

    void replaceShopItems();
    std::vector<CItem*> _shopItems;

    unsigned long _turns;
};
