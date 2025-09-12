#include "moduleressources.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "fishingvillage/cfishingvillage.h"
#include "fishingvillage/items/cboatpart.h"
#include "fishingvillage/items/cfishingrodpart.h"
#include "fishingvillage/tasks/cbuildequipmenttask.h"
#include "fishingvillage/tasks/cfishingvilletowntask.h"
#include "randomizer.h"

#include <algorithm>
#include <format>

std::string FishingVillageRessources::moduleNameMakeRod()
{
    return "FishingVillage_MakeRod";
}

std::string FishingVillageRessources::moduleNameMakeBoat()
{
    return "FishingVillage_MakeBoat";
}

std::string FishingVillageRessources::moduleNameFishLegend()
{
    return "FishingVillage_FishLegend";
}

void FishingVillageRessources::initModuleMakeRod()
{
    CGameManagement::getItemFactoryInstance()->registerLootItemGenerator(
        moduleNameMakeRod(), []() { return new CFishingRodPart(); }, 50);
    CGameManagement::getInstance()->placeTask(new CBuildEquipmentTask(moduleNameMakeRod()),
                                              CFishingVillage::fishingVillageFilter());
}

void FishingVillageRessources::initModuleMakeBoat()
{
    CGameManagement::getItemFactoryInstance()->registerLootItemGenerator(
        moduleNameMakeBoat(), []() { return new CBoatPart(); }, 50);
    CGameManagement::getInstance()->placeTask(new CBuildEquipmentTask(moduleNameMakeBoat()),
                                              CFishingVillage::fishingVillageFilter());
}

void FishingVillageRessources::initModuleFishLegend()
{
    CGameManagement::getInstance()->placeTaskOnTown(new CFishingVilleTownTask());
}

void FishingVillageRessources::deInitModuleMakeBoat()
{
}

void FishingVillageRessources::deInitModuleFishLegend()
{
}

void FishingVillageRessources::deInitModuleMakeRod()
{
}

void FishingVillageRessources::initWorldMap(std::vector<CRoom*>& rooms)
{
    rooms.push_back(new CFishingVillage());
}

CRoom* FishingVillageRessources::roomFactory(const std::string_view& objectName)
{
    if (TagNames::FishingVille::fishingVille.compare(objectName) == 0)
    {
        return new CFishingVillage();
    }
    return nullptr;
}

std::string FishingVillageRessources::fishingVilleName()
{
    return std::format("{}Middlesbron {}Cove{}", CC::fgLightGreen(), CC::fgLightBlue(), CC::ccReset());
}

std::string FishingVillageRessources::getFish(const EFishLevel level)
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

int FishingVillageRessources::getFishPrice(const EFishLevel level)
{
    switch (level)
    {
    case FishingVillageRessources::EFishLevel::eCommon:
    default:
        return 10;
    case FishingVillageRessources::EFishLevel::eUncommon:
        return 25;
    case FishingVillageRessources::EFishLevel::eRare:
        return 50;
    case FishingVillageRessources::EFishLevel::eUltraRare:
        return 500;
    case FishingVillageRessources::EFishLevel::eLegend:
        return 100000;
    }
}

FishingVillageRessources::EFishLevel FishingVillageRessources::getRandomRarity(const unsigned int rodLevel,
                                                                               const unsigned int boatLevel)
{
    std::vector<FishingVillageRessources::EFishLevel> fishes;

    auto add = [&fishes](const unsigned int number, const FishingVillageRessources::EFishLevel level)
    {
        for (auto i = 0U; i < number; i++)
        {
            fishes.push_back(level);
        }
    };

    add(50, FishingVillageRessources::EFishLevel::eCommon);
    add(25, FishingVillageRessources::EFishLevel::eUncommon);
    add(10, FishingVillageRessources::EFishLevel::eRare);
    add(5, FishingVillageRessources::EFishLevel::eUltraRare);
    add(1, FishingVillageRessources::EFishLevel::eLegend);

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

std::string FishingVillageRessources::questLogMakeRod()
{
    return "Build a fishing rod";
}

std::string FishingVillageRessources::questLogMAkeBoat()
{
    return "Build a boat";
}

std::string FishingVillageRessources::questLogFishLegend()
{
    return std::format("Catch the legendary {}", getFish(EFishLevel::eLegend));
}
