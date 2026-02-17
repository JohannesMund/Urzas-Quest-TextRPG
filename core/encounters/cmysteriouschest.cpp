#include "cmysteriouschest.h"
#include "cgamemanagement.h"
#include "citemfactory.h"
#include "clivingchest.h"
#include "cmenu.h"
#include "console.h"
#include "randomizer.h"

CMysteriousChest::CMysteriousChest() : CEncounter()
{
    _isSingleExecution = false;
    _type = CEncounter::eField | CEncounter::eDungeon;
}

void CMysteriousChest::execute(const std::string_view&)
{
    CEncounter::execute();
    _hasBeenExecuted = true;

    Console::printLn(
        "Wandering through the lands, you see a mysterious chest, standing there. It does not make any sense to put a "
        "chest there. It is rather odd, to see a chest at this place. This could be a trap!");
    Console::printLn("But after all, this is a chest. we should open it!");

    CMenu menu;
    CMenuAction openAction = menu.createAction({"Open the chest"});
    CMenuAction goAction = menu.createAction({"Go away"});

    menu.addMenuGroup({openAction}, {goAction});

    if (menu.execute() == goAction)
    {
        Console::br();
        Console::printLn(
            "This chest does not belong there, and you should not open it. You here the cackle of a chicken from far.");
        return;
    }

    Console::br();
    Console::printLn("This is too tempting. You go over to the chest and open it.");

    int goodStuffBonus = 0;
    if (Randomizer::getRandom(3) == 0)
    {
        Console::printLn("just to realize, that this was a mistake! This is a living chest, and it attacks you!");

        CLivingChest chest;
        CBattle battle(&chest);
        battle.fight();

        if (!chest.isDead())
        {
            Console::printLn("You manage to escape. This was one scary monster!");
            return;
        }
        goodStuffBonus += 2;
    }

    auto reward = Randomizer::getRandom(15) + goodStuffBonus;
    unsigned int gold = CGameManagement::getPlayerInstance()->level() * 750;

    if (reward >= 15)
    {
        CGameManagement::getInventoryInstance()->addAwesomneItem();
    }
    if (reward >= 7)
    {
        gold -= CGameManagement::getPlayerInstance()->level() * 250;
        CGameManagement::getInventoryInstance()->addShopItem();
        if (Randomizer::getRandom(2) == 0)
        {
            CGameManagement::getInventoryInstance()->addShopItem();
        }
    }
    if (reward >= 5)
    {
        CGameManagement::getInventoryInstance()->addShopItem();
    }
    CGameManagement::getPlayerInstance()->gainGold(gold);
}

unsigned int CMysteriousChest::encounterChance(const EEncounterType&, const std::string_view&) const
{
    return 3;
}

std::string CMysteriousChest::name() const
{
    return "Myterious Chest";
}

std::string CMysteriousChest::translatorModuleName() const
{
    return std::string();
}
