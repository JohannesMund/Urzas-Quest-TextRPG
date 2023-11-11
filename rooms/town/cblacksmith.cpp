#include "cblacksmith.h"
#include "cequipment.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "console.h"

#include <format>

CBlackSmith::CBlackSmith()
{
}

void CBlackSmith::execute()
{
    CMenu menu;
    menu.addMenuGroup({menu.createAction("Enhance Item")}, {CMenu::exitAction()});
    CMenu::Action input;

    do
    {
        Console::cls();
        Console::printLn(
            "The Blacksmith in town. It is hot, it is dirty, the sound of a hammer hitting an anvil fills the air.");
        Console::printLn(
            "A grumpy old man, probably the blacksmith looks at you suspiciously and asks what he can do for you.");
        Console::hr();

        input = menu.execute();

        if (input.key == 'e')
        {
            enhanceItem();
        }

    } while (!CMenu::exit(input));
}

void CBlackSmith::enhanceItem()
{
    auto items = CGameManagement::getInventoryInstance()->getEnhancableEquipment();
    if (items.size() == 0)
    {
        Console::printLn("You look through your pockets and find no enhancable items.");
        return;
    }

    int number = 0;
    std::vector<CEquipment*> enhancableItems;
    Console::printLn("You look through your pockets and find the following items, that can be enhanced:");
    for (auto item : items)
    {
        auto cost = item->upgradeCost();

        if (cost <= CGameManagement::getPlayerInstance()->gold())
        {
            number++;
            enhancableItems.push_back(item);
            Console::printLn(std::format("[{:3}] {} ({} Gold)", number, item->name(), cost));
        }
        else
        {
            Console::printLn(std::format("[   ] {} ({} Gold)", item->name(), cost));
        }
    }

    if (enhancableItems.size() > 0)
    {
        auto idx = Console::getNumberInputWithEcho(1, number);

        if (idx.has_value())
        {
            auto item = enhancableItems.at(*idx - 1);
            auto cost = item->upgradeCost();
            item->enhance();
            CGameManagement::getPlayerInstance()->addGold(cost * -1);
        }
    }
    Console::confirmToContinue();
}
