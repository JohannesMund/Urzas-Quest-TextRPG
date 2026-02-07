#include "cgofishing.h"
#include "cequipment.h"
#include "cgamemanagement.h"
#include "citemfactory.h"
#include "cmenu.h"
#include "colorize.h"
#include "console.h"
#include "fishingvillage/items/cboat.h"
#include "fishingvillage/items/cfish.h"
#include "fishingvillage/items/cfishingrod.h"
#include "fishingvillage/moduleressources.h"
#include "randomizer.h"

#include <format>

CGoFishing::CGoFishing()
{
}

void CGoFishing::execute()
{
    init();

    CMenu menu(FishingVillageMakeRod::moduleName());

    CMenu::ActionList actions;
    CMenuAction catchAction = menu.createAction("Catch fish");

    if (_fishingRod != nullptr || _boat != nullptr)
    {
        actions.push_back(catchAction);
    }
    menu.addMenuGroup(actions, {CMenu::exit()});
    CMenuAction input;

    do
    {
        Console::cls();
        Console::printLn(
            "There is a long jetty with some boats. You can walk down the jetty and try fishing yourself.");

        printItemLevels();

        input = menu.execute();
        if (input == catchAction)
        {
            catchAFish();
        }

    } while (input != CMenu::exit());
}

void CGoFishing::init()
{
    auto items = CGameManagement::getInventoryInstance()->getItemsByFilter(CFishingRod::fishingRodFilter());
    if (items.size())
    {
        auto rod = dynamic_cast<CFishingRod*>(items.at(0));
        if (rod != nullptr)
        {
            _fishingRod = rod;
        }
    }

    items = CGameManagement::getInventoryInstance()->getItemsByFilter(CBoat::boatFilter());
    if (items.size())
    {
        auto boat = dynamic_cast<CBoat*>(items.at(0));
        if (boat != nullptr)
        {
            _boat = boat;
        }
    }
}

void CGoFishing::printItemLevels()
{

    bool haveFishingRod = (_fishingRod != nullptr);
    bool haveBoat = (_boat != nullptr);

    if (!haveFishingRod)
    {
        Console::printLn("If you had a fishing rod, you could use it for fishing");
    }
    if (!haveBoat)
    {
        Console::printLn(
            "If you had a boat, you could use it to get out into the lake and catch bigger and better fish.");
    }
    Console::br();
    if (!haveFishingRod && !haveBoat)
    {
        Console::printLn("unfortunately you have neither");
    }
    else
    {
        Console::printLn(
            "You have what it takes, to catch at least something, so you could very well try to catch some fish.");
        std::string fishingRodString;
        if (haveFishingRod)
        {
            fishingRodString = std::format("{} (Level {})", _fishingRod->name(), _fishingRod->level());
        }
        std::string boatString;
        if (haveBoat)
        {
            boatString = std::format("{} (Level {})", _boat->name(), _boat->level());
        }
        Console::br();
        Console::printLnWithSpacer(fishingRodString, boatString);
    }

    Console::br();
}

void CGoFishing::catchAFish()
{
    auto rodLevel = _fishingRod == nullptr ? 0 : _fishingRod->level();
    auto boatLevel = _boat == nullptr ? 0 : _boat->level();

    Console::br();
    auto i = Randomizer::getRandom(55 + (rodLevel * 3) + (boatLevel * 6));

    if (i < 25)
    {
        Console::printLn(std::format("You catch nothing. But as a legendary {} you too would not let yourself beeing "
                                     "caught by crappy equipment like yours.",
                                     FishingVillage::getFish(FishingVillage::EFishLevel::eLegend)));
    }
    else if (i < 50)
    {
        auto item = CGameManagement::getItemFactoryInstance()->makeLootItem();
        Console::printLn(std::format("You sit there and wath the pose of your fishing rod, waiting for something to "
                                     "happen... and wait, and sit, and sit, ant wait. and si... until all of a sudden "
                                     "your fishing rod moves. You pull it in and see that you have caught a {}.",
                                     item->name()));
        Console::printLn("It is not a fish, but it is also not nothing.");
        CGameManagement::getInventoryInstance()->addItem(item);
    }
    else
    {
        auto fish = new CFish(rodLevel, boatLevel);
        Console::printLn(std::format(
            "You sit there and wath the pose of your fishing rod, waiting for something to "
            "happen... and wait, and sit, and sit, ant wait. and si... until all of a sudden "
            "your fishing rod moves. You try to pull it in, but it fights back. This time, there is actually a living "
            "beeing on the other side of the fishing line! You pull and you fight, and the fish fights and pulls, and "
            "after some pulling and fighting, you win. YOu caught a beautiful {}!",
            fish->name()));
        CGameManagement::getInventoryInstance()->addItem(fish);
    }
    Console::br();
    Console::confirmToContinue();
}
