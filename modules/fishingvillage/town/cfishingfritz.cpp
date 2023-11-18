#include "cfishingfritz.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "colorconsole.h"
#include "console.h"
#include "fishingvillage/items/cboat.h"
#include "fishingvillage/items/cboatpart.h"
#include "fishingvillage/items/cfish.h"
#include "fishingvillage/items/cfishingrod.h"
#include "fishingvillage/items/cfishingrodpart.h"
#include "fishingvillage/moduleressources.h"

#include <format>

CFishingFritz::CFishingFritz()
{
}

void CFishingFritz::execute()
{
    CMenu::Action input;

    do
    {
        printHeader();

        CMenu menu;

        std::vector<CMenu::Action> moduleActionList;
        std::vector<CMenu::Action> defaultActionList;

        if (!isOpen())
        {
            Console::printLn(
                std::format("{}'s fishing shop is an old, ramshackle hut. It is good, that the weather here is always "
                            "sunny and clear, because this hut would probably collapse, when hit by a medium strong "
                            "wind. Also, it will offer not much protection against rain, snow, or even cold.",
                            FishingVillageRessources::fishingFritz()));
            Console::printLn("There is a sign on the locked door reding:");
            Console::printLn("\"Gone fishing, come back later\"", Console::EAlignment::eCenter);
        }
        else
        {
            if (hasFish())
            {
                defaultActionList.push_back(menu.createAction(sellYourFish(), 'S'));
            }

            if (CGameManagement::getInventoryInstance()->hasItem(CFishingRod::fishingRodFilter()))
            {
                defaultActionList.push_back(menu.createAction("Enhance Equipment", 'E'));
            }

            if (isMakeRodActive())
            {
                moduleActionList.push_back(menu.createAction("Ask about Fishing", 'A'));
            }
            else if (isMakeBoatActive())
            {
                moduleActionList.push_back(menu.createAction("Ask about Boating", 'A'));
            }
            else
            {
                moduleActionList.push_back(menu.createAction("Ask about Information", 'A'));
            }
        }

        menu.addMenuGroup(moduleActionList);
        menu.addMenuGroup(defaultActionList, {CMenu::exit()});
        input = menu.execute();

        if (input.key == 'a')
        {
            ask();
        }
        if (input.key == 's')
        {
            sell();
        }
        if (input.key == 'e')
        {
            enhance();
        }

    } while (input != CMenu::exit());
}

void CFishingFritz::printHeader() const
{
    Console::cls();
    Console::printLn(std::format("{}", FishingVillageRessources::fishingFritz()), Console::EAlignment::eCenter);
    Console::printLn(std::format("Fishing fresh fish since 832 ad. dragonis", FishingVillageRessources::fishingFritz()),
                     Console::EAlignment::eCenter);
    Console::br();
}

bool CFishingFritz::isOpen() const
{
    return CGameManagement::getProgressionInstance()->isModuleActive(FishingVillageRessources::moduleNameMakeRod()) ||
           CGameManagement::getProgressionInstance()->isModuleFinished(FishingVillageRessources::moduleNameMakeRod());
}

void CFishingFritz::ask() const
{
    if (isMakeRodActive())
    {
        buildRod();
    }
    else if (isMakeBoatActive())
    {
        buildBoat();
    }
    else
    {
        getInformation();
    }
}

void CFishingFritz::buildRod() const
{
    Console::printLn("You want to get into the fishing businnes, and thos guy seems to be exactly the right one to ask "
                     "how. He tells you about fishes, fishing rods, baits, boars and the weather, but after all, the "
                     "first thing you need is a fishing rod.");

    Console::printLn(std::format("{} will build you one fishing rod for free, if you bring hin the following items:",
                                 FishingVillageRessources::fishingFritz()));

    Console::printLn(std::format("{0}x {1}, {0}x {2} and {0}x {3}",
                                 FishingVillageRessources::necessaryRodParts,
                                 CFishingRodPart::nameForPart(CFishingRodPart::EPart::eRod),
                                 CFishingRodPart::nameForPart(CFishingRodPart::EPart::eThread),
                                 CFishingRodPart::nameForPart(CFishingRodPart::EPart::eHook)));
    Console::br();
    Console::printLn("You have:");

    unsigned int partsComplete = 0;
    for (const auto& part :
         {CFishingRodPart::EPart::eRod, CFishingRodPart::EPart::eThread, CFishingRodPart::EPart::eHook})
    {
        auto items = CGameManagement::getInventoryInstance()->getCompressedItemMap(CFishingRodPart::partFilter(part));
        auto count = 0;
        if (items.size())
        {
            count = items.at(0).first;
            if (count >= FishingVillageRessources::necessaryRodParts)
            {
                partsComplete++;
            }
        }
        Console::printLn(std::format("{}: {}", CFishingRodPart::nameForPart(part), count));
    }
    Console::br();
    if (partsComplete >= 3)
    {
        CFishingRod* rod = new CFishingRod();
        Console::printLn(
            std::format("{} taks your parts, and starts working. After s short while, he gives you your brand new {}.",
                        FishingVillageRessources::fishingFritz(),
                        rod->name()));

        for (const auto& part :
             {CFishingRodPart::EPart::eRod, CFishingRodPart::EPart::eThread, CFishingRodPart::EPart::eHook})
        {
            for (int i = 0; i < FishingVillageRessources::necessaryRodParts; i++)
            {
                CGameManagement::getInventoryInstance()->removeItem(CFishingRodPart::nameForPart(part));
            }
        }
        Console::br();
        CGameManagement::getInventoryInstance()->addItem(rod);
        Console::br();
        CGameManagement::getProgressionInstance()->reportModuleFinished(FishingVillageRessources::moduleNameMakeRod());
        CGameManagement::getInstance()->unregisterEncounterByModuleName(FishingVillageRessources::moduleNameMakeRod());
    }
    else
    {
        Console::printLn("This is not enough, you will have to find more");
    }

    Console::confirmToContinue();
}

void CFishingFritz::buildBoat() const
{
    Console::printLn("For better fish, you need a boat. Using a boat you can get out onto the lake and catch better "
                     "fish from the deeper waters.");

    Console::printLn(std::format("{} will build you one boat for free, if you bring hin the following items:",
                                 FishingVillageRessources::fishingFritz()));

    Console::printLn(std::format("{0}x {1}, {0}x {2} and {0}x {3}",
                                 FishingVillageRessources::necessaryBoatParts,
                                 CBoatPart::nameForPart(CBoatPart::EPart::eBoard),
                                 CBoatPart::nameForPart(CBoatPart::EPart::eNail),
                                 CBoatPart::nameForPart(CBoatPart::EPart::eRope)));
    Console::br();
    Console::printLn("You have:");

    unsigned int partsComplete = 0;
    for (const auto& part : {CBoatPart::EPart::eBoard, CBoatPart::EPart::eNail, CBoatPart::EPart::eRope})
    {
        auto items = CGameManagement::getInventoryInstance()->getCompressedItemMap(CBoatPart::partFilter(part));
        auto count = 0;
        if (items.size())
        {
            count = items.at(0).first;
            if (count >= FishingVillageRessources::necessaryBoatParts)
            {
                partsComplete++;
            }
        }
        Console::printLn(std::format("{}: {}", CBoatPart::nameForPart(part), count));
    }
    Console::br();
    if (partsComplete >= 3)
    {
        CBoat* boat = new CBoat();
        Console::printLn(
            std::format("{} taks your parts, and starts working. After s short while, he gives you your brand new {}.",
                        FishingVillageRessources::fishingFritz(),
                        boat->name()));

        for (const auto& part : {CBoatPart::EPart::eBoard, CBoatPart::EPart::eNail, CBoatPart::EPart::eRope})
        {
            for (int i = 0; i < FishingVillageRessources::necessaryRodParts; i++)
            {
                CGameManagement::getInventoryInstance()->removeItem(CBoatPart::nameForPart(part));
            }
        }
        Console::br();
        CGameManagement::getInventoryInstance()->addItem(boat);
        Console::br();
        CGameManagement::getProgressionInstance()->reportModuleFinished(FishingVillageRessources::moduleNameMakeBoat());
        CGameManagement::getInstance()->unregisterEncounterByModuleName(FishingVillageRessources::moduleNameMakeBoat());
    }
    else
    {
        Console::printLn("This is not enough, you will have to find more");
    }

    Console::confirmToContinue();
}

void CFishingFritz::getInformation() const
{
}

void CFishingFritz::sell() const
{
    auto items = CGameManagement::getInventoryInstance()->getItemsByFilter(CFish::fishFilter());
    if (items.size() == 0)
    {
        return;
    };
    for (const auto& item : items)
    {
        CGameManagement::getPlayerInstance()->addGold(item->value());
        CGameManagement::getInventoryInstance()->removeItem(item);
    }
    Console::confirmToContinue();
}

void CFishingFritz::enhance() const
{
    auto items = CGameManagement::getInventoryInstance()->getEnhancableEquipment();
    CInventory::EnhancableEquipmentList enhancableItems;

    auto checkAndPrint = [&enhancableItems](CEquipment* item)
    {
        if (item == nullptr)
        {
            return;
        }
        auto cost = item->upgradeCost();

        if (cost <= CGameManagement::getPlayerInstance()->gold())
        {
            enhancableItems.push_back(item);
            Console::printLn(std::format("[{:3}] {} ({} Gold)", enhancableItems.size(), item->name(), cost));
        }
        else
        {
            Console::printLn(std::format("[   ] {} ({} Gold)", item->name(), cost));
        }
    };

    for (auto& item : items)
    {
        checkAndPrint(dynamic_cast<CFishingRod*>(item));
        checkAndPrint(dynamic_cast<CBoat*>(item));
    }

    if (enhancableItems.size() > 0)
    {
        auto idx = Console::getNumberInputWithEcho(1, enhancableItems.size());
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

bool CFishingFritz::isMakeRodActive() const
{
    return CGameManagement::getProgressionInstance()->isModuleActive(FishingVillageRessources::moduleNameMakeRod());
}

bool CFishingFritz::isMakeBoatActive() const
{
    return CGameManagement::getProgressionInstance()->isModuleActive(FishingVillageRessources::moduleNameMakeBoat());
}

bool CFishingFritz::hasFish() const
{
    return CGameManagement::getInventoryInstance()->hasItem(CFish::fishFilter());
}

std::string CFishingFritz::sellYourFish() const
{
    auto items = CGameManagement::getInventoryInstance()->getItemsByFilter(CFish::fishFilter());
    if (items.size() == 0)
    {
        return "";
    }

    unsigned int value = 0U;
    for (const auto& item : items)
    {
        value += item->value();
    }

    return std::format("Sell your fish ({} Gold)", value);
}
