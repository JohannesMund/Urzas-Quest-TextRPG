#include "moduleressources.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "fishingvillage/cfishingvillage.h"
#include "fishingvillage/items/cboat.h"
#include "fishingvillage/items/cboatpart.h"
#include "fishingvillage/items/cfish.h"
#include "fishingvillage/items/cfishingrod.h"
#include "fishingvillage/items/cfishingrodpart.h"
#include "fishingvillage/tasks/cbuildequipmenttask.h"
#include "fishingvillage/tasks/cfishingvilletowntask.h"
#include "randomizer.h"

#include <algorithm>
#include <format>

std::string FishingVillageMakeRod::moduleName()
{
    return "FishingVillage_MakeRod";
}

std::string FishingVillageMakeBoat::moduleName()
{
    return "FishingVillage_MakeBoat";
}

std::string FishingVillageFishLegend::moduleName()
{
    return "FishingVillage_FishLegend";
}

std::string FishingVillage::moduleName()
{
    return "FishingVillage";
}

std::string FishingVillage::fishingVilleName()
{
    return std::format("{}Middlesbron {}Cove{}", CC::fgLightGreen(), CC::fgLightBlue(), CC::ccReset());
}

std::string FishingVillage::getFish(const EFishLevel level)
{
    switch (level)
    {
    case EFishLevel::eCommon:
        return std::format("{}Red Snapper{}", CC::fgLightRed(), CC::ccReset());

    case EFishLevel::eUncommon:
        return std::format("{}Carp{}", CC::fgYellow(), CC::ccReset());
    case EFishLevel::eRare:
        return std::format("{}T{}r{}o{}u{}t{}",
                           CC::fgRed(),
                           CC::fgYellow(),
                           CC::fgLightYellow(),
                           CC::fgLightGreen(),
                           CC::fgLightBlue(),
                           CC::ccReset());
    case EFishLevel::eUltraRare:
        return std::format("{0}M{1}a{1}g{0}i{1}c{0}a{1}r{0}p{2}", CC::fgRed(), CC::fgWhite(), CC::ccReset());
    case EFishLevel::eLegend:
        return std::format("{0}yellow {1}red {2}feathered {0}d{1}r{0}a{1}g{0}o{1}n {0}f{1}i{0}s{1}h{2}",
                           CC::fgRed(),
                           CC::fgLightYellow(),
                           CC::ccReset());
    }
}

int FishingVillage::getFishPrice(const EFishLevel level)
{
    switch (level)
    {
    case FishingVillage::EFishLevel::eCommon:
    default:
        return 10;
    case FishingVillage::EFishLevel::eUncommon:
        return 25;
    case FishingVillage::EFishLevel::eRare:
        return 50;
    case FishingVillage::EFishLevel::eUltraRare:
        return 500;
    case FishingVillage::EFishLevel::eLegend:
        return 100000;
    }
}

FishingVillage::EFishLevel FishingVillage::getRandomRarity(const unsigned int rodLevel, const unsigned int boatLevel)
{
    std::vector<FishingVillage::EFishLevel> fishes;

    auto add = [&fishes](const unsigned int number, const FishingVillage::EFishLevel level)
    {
        for (auto i = 0U; i < number; i++)
        {
            fishes.push_back(level);
        }
    };

    add(50, FishingVillage::EFishLevel::eCommon);
    add(25, FishingVillage::EFishLevel::eUncommon);
    add(10, FishingVillage::EFishLevel::eRare);
    add(5, FishingVillage::EFishLevel::eUltraRare);
    add(1, FishingVillage::EFishLevel::eLegend);

    auto calcBonus = [](unsigned int level) -> unsigned int
    {
        if (level == 0)
        {
            return 0U;
        }
        return Randomizer::getRandom(level * 2) + 1 + level;
    };

    unsigned int i = (fishes.size() - 1) - rodLevelCap * 3 - boatLevelCap * 3;
    auto rnd = std::min(fishes.size() - 1,
                        (size_t)(Randomizer::getRandom(i) + calcBonus(rodLevel) + calcBonus(boatLevel) + 15));
    return fishes.at(rnd);
}

Module::ModuleInfo FishingVillageMakeRod::moduleInfo()
{
    const auto itemFactory = [](const std::string_view& objectName) -> CItem*
    {
        if (TagNames::FishingVille::boat.compare(objectName) == 0)
        {
            return new CBoat();
        }
        if (TagNames::FishingVille::boatPart.compare(objectName) == 0)
        {
            return new CBoatPart();
        }
        if (TagNames::FishingVille::fish.compare(objectName) == 0)
        {
            return new CFish();
        }
        if (TagNames::FishingVille::fishingRod.compare(objectName) == 0)
        {
            return new CFishingRod();
        }
        if (TagNames::FishingVille::fishingRodPart.compare(objectName) == 0)
        {
            return new CFishingRodPart();
        }

        return nullptr;
    };

    const auto roomFactory = [](const std::string_view& objectName) -> CRoom*
    {
        if (TagNames::FishingVille::fishingVille.compare(objectName) == 0)
        {
            return new CFishingVillage();
        }
        return nullptr;
    };

    Module::ModuleInfo moduleInfo = Module::ModuleInfo();

    moduleInfo.moduleName = moduleName();
    moduleInfo.translatorFile = "fishingvillage";
    moduleInfo.gameStage = Module::EGameStage::eSeenBard;

    moduleInfo.questLogFunction = []() { return "Build a fishing rod"; };
    moduleInfo.initFunction = []()
    {
        CGameManagement::getItemFactoryInstance()->registerLootItemGenerator(
            moduleName(), []() { return new CFishingRodPart(); }, 50);
        CGameManagement::getInstance()->placeTask(new CBuildEquipmentTask(moduleName()),
                                                  CFishingVillage::fishingVillageFilter());
    };

    moduleInfo.initWorldMapFunction = [](std::vector<CRoom*>& rooms) { rooms.push_back(new CFishingVillage()); };
    moduleInfo.roomFactory = roomFactory;
    moduleInfo.itemFactory = itemFactory;

    return moduleInfo;
}

Module::ModuleInfo FishingVillageMakeBoat::moduleInfo()
{
    Module::ModuleInfo moduleInfo = Module::ModuleInfo();

    moduleInfo.moduleName = moduleName();
    moduleInfo.translatorFile = "fishingvillage";
    moduleInfo.gameStage = Module::EGameStage::eProvenAsHero;

    moduleInfo.questLogFunction = []() { return "Build a boat"; };
    moduleInfo.initFunction = []()
    {
        CGameManagement::getItemFactoryInstance()->registerLootItemGenerator(
            moduleName(), []() { return new CBoatPart(); }, 50);
        CGameManagement::getInstance()->placeTask(new CBuildEquipmentTask(moduleName()),
                                                  CFishingVillage::fishingVillageFilter());
    };

    return moduleInfo;
}

Module::ModuleInfo FishingVillageFishLegend::moduleInfo()
{
    Module::ModuleInfo moduleInfo = Module::ModuleInfo();

    moduleInfo.moduleName = moduleName();
    moduleInfo.translatorFile = "fishingvillage";
    moduleInfo.gameStage = Module::EGameStage::eLearnedAboutCult;

    moduleInfo.questLogFunction = []()
    { return std::format("Catch the legendary {}", getFish(FishingVillage::EFishLevel::eLegend)); };
    moduleInfo.initFunction = []() { CGameManagement::getInstance()->placeTaskOnTown(new CFishingVilleTownTask()); };

    return moduleInfo;
}
