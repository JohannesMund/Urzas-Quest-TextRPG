#include "cbuildequipmenttask.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "console.h"
#include "fishingvillage/items/cboat.h"
#include "fishingvillage/items/cboatpart.h"
#include "fishingvillage/items/cfishingrod.h"
#include "fishingvillage/items/cfishingrodpart.h"
#include "fishingvillage/moduleressources.h"

#include <format>

CBuildEquipmentTask::CBuildEquipmentTask(const std::string_view& moduleName) :
    CTask(TagNames::FishingVille::buildEquipmentTask),
    _moduleName(moduleName)
{
    _isAutoExecute = false;
}

void CBuildEquipmentTask::execute()
{

    if (_moduleName.compare(FishingVillageRessources::moduleNameMakeRod()) == 0)
    {
        buildRod();
    }
    else
    {
        buildBoat();
    }
}

std::string CBuildEquipmentTask::taskNav() const
{
    if (_moduleName.compare(FishingVillageRessources::moduleNameMakeRod()) == 0)
    {
        return "Build your Fishing Rod";
    }
    return "Build your Boat";
}

void CBuildEquipmentTask::buildBoat()
{
    Console::printLn("For better fish, you need a boat. Using a boat you can get out onto the lake and catch better "
                     "fish from the deeper waters.");

    Console::printLn(std::format("{} will build you one boat for free, if you bring hin the following items:",
                                 Ressources::Game::fishingFritz()));

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
                        Ressources::Game::fishingFritz(),
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
        CGameManagement::getItemFactoryInstance()->unregisterLootItemGeneratorByName(
            FishingVillageRessources::moduleNameMakeBoat());

        _isFinished = true;
    }
    else
    {
        Console::printLn("This is not enough, you will have to find more");
    }
}

void CBuildEquipmentTask::buildRod()
{
    Console::printLn("You want to get into the fishing businnes, and thos guy seems to be exactly the right one to ask "
                     "how. He tells you about fishes, fishing rods, baits, boars and the weather, but after all, the "
                     "first thing you need is a fishing rod.");

    Console::printLn(std::format("{} will build you one fishing rod for free, if you bring hin the following items:",
                                 Ressources::Game::fishingFritz()));

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
                        Ressources::Game::fishingFritz(),
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
        CGameManagement::getItemFactoryInstance()->unregisterLootItemGeneratorByName(
            FishingVillageRessources::moduleNameMakeRod());
        _isFinished = true;
    }
    else
    {
        Console::printLn("This is not enough, you will have to find more");
    }
}
