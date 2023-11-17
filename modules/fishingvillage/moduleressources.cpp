#include "moduleressources.h"
#include "colorconsole.h"
#include "fishingvillage/town/cfishingvillage.h"

#include <format>

std::string FishingVillageRessources::moduleName()
{
    return "FishingVillage";
}

void FishingVillageRessources::initModule()
{
}

void FishingVillageRessources::deInitModule()
{
}

void FishingVillageRessources::initWorldMap(std::vector<CRoom*>& rooms)
{
    rooms.push_back(new CFishingVillage());
}

std::string FishingVillageRessources::fishingVilleName()
{
    return std::format("{}Middlesbron {}Cove{}", CC::fgLightGreen(), CC::fgLightBlue(), CC::ccReset());
}

std::string FishingVillageRessources::fishingFritz()
{
    return std::format("F{0}ishing{1} F{0}ritz{2}", CC::fgBlue(), CC::fgWhite(), CC::ccReset());
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
